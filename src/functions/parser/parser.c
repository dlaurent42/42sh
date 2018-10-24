/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:20:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 15:45:41 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_err(char *cmd, int err)
{
	if (err == 1)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(cmd, 2);
		return (127);
	}
	if (err == 2)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(cmd, 2);
		return (126);
	}
	return (0);
}

static char	sh_command_found(t_shell *sh, t_env *env, t_bin *bin, char **arr)
{
	int			i;
	t_bin_obj	*obj;

	i = 0;
	if (arr && arr[0] && arr[0][0] == '/')
	{
		if (access(arr[0], F_OK) != 0)
			return (sh_command_err(arr[0], 1));
		if (access(arr[0], R_OK) != 0 || access(arr[0], X_OK) != 0)
			return (sh_command_err(arr[0], 2));
	}
	else if (arr && arr[0] && sh_is_not_builtin(arr[0]))
	{
		if (!(obj = bin_search(bin, arr[0])) || access(obj->path, F_OK) != 0)
			return (sh_command_err(arr[0], 1));
		if (access(obj->path, R_OK) != 0 || access(obj->path, X_OK) != 0)
			return (sh_command_err(arr[0], 2));
		ft_strdel(&arr[0]);
		arr[0] = ft_strdups(obj->path);
	}
	while (arr[++i])
		sh_remove_useless_quotes(arr[i]);
	return (sh_command_dispatch(sh, env, arr));
}


/*
** IDEA: Only for testing purposes.
*/
char	sh_test_command_found(t_shell *sh, t_env *env, t_bin *bin,
	char **arg)
{
	int		i;
	char	*tmp;
	char	*str;

	i = 0;
	if (arg && arg[0] && arg[0][0] == '.' && arg[0][1] == '/')
	{
		tmp = realpath(arg[0], NULL);
		ft_strdel(&arg[0]);
		arg[0] = tmp;
	}
	str = ft_itoa(sh_command_found(sh, env, bin, &arg[0]));
	if ((env_search(sh->env, "?") || sh->env->count + 1 < sh->env->size) && str)
		env_insert_protected(sh, sh->env, "?", str);
	// if (arg)
	// 	while (arg[i])
	// 	{
	// 		ft_strdel(&arg[i]);
	// 		i++;
	// 	}
	// (arg) ? free(arg) : 0;
	ft_strdel(&str);
	return (1);
}

static void	sh_command_parse_dispatch(t_shell *sh, t_env *env, t_bin *bin,
	char *str)
{
	int		i;
	char	*tmp;
	char	**arg;

	i = 0;
	if (!(arg = sh_command_build(str)))
		return (ft_strdel(&str));
	if (arg && arg[0] && arg[0][0] == '.' && arg[0][1] == '/')
	{
		tmp = realpath(arg[0], NULL);
		ft_strdel(&arg[0]);
		arg[0] = tmp;
	}
	ft_strdel(&str);
	str = ft_itoa(sh_command_found(sh, env, bin, &arg[0]));
	if ((env_search(sh->env, "?") || sh->env->count + 1 < sh->env->size) && str)
		env_insert_protected(sh, sh->env, "?", str);
	if (arg)
		while (arg[i])
		{
			ft_strdel(&arg[i]);
			i++;
		}
	(arg) ? free(arg) : 0;
	ft_strdel(&str);
}

void		sh_command_parser(t_shell *sh, t_env *env, t_bin *bin, char *str)
{
	int				i;
	int				j;
	bool			in_dquote;
	bool			in_squote;

	i = 0;
	j = 0;
	in_dquote = FALSE;
	in_squote = FALSE;
	while (str[i])
	{
		if (str[i] == '"')
			in_dquote = (in_dquote || in_squote) ? FALSE : TRUE;
		else if (str[i] == '\'')
			in_squote = (in_dquote || in_squote) ? FALSE : TRUE;
		else if (str[i] == ';' && !in_dquote && !in_squote)
		{
			sh_command_parse_dispatch(sh, env, bin, ft_strsub(str, j, i - j));
			j = i + 1;
		}
		i++;
	}
	sh_command_parse_dispatch(sh, env, bin, ft_strsub(str, j, i - j));
}
