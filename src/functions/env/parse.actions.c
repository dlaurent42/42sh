/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:11:48 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/08 10:53:32 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_env_empty(t_env *env, bool verbose)
{
	size_t		i;
	t_env_item	*item;

	i = 0;
	if (!env)
		return (0);
	while (i < env->count)
	{
		item = env->items[i];
		if (item && item != &env->del)
		{
			env_delete_specified_item(item);
			env->items[i] = &env->del;
		}
		i++;
	}
	i = 0;
	while (env->environment[i])
	{
		ft_strdel(&env->environment[i]);
		i++;
	}
	(verbose) ? ft_putendl("#env clearing environ") : 0;
	return ((env->count = 0));
}

char	sh_env_unset(t_env *env, char *arg, bool verbose)
{
	char	*arg_parsed;

	if (ft_strcountif(arg, '='))
		return (-1);
	if (!(arg_parsed = sh_unsetenv_parse(ft_strdups(arg))))
		return (-5);
	if (verbose)
	{
		ft_putstr("#env unset:     ");
		ft_putendl(arg_parsed);
	}
	env_delete_item(env, arg_parsed);
	ft_strdel(&arg_parsed);
	return (0);
}

char	sh_env_path(char *arg, char **path)
{
	size_t	len;

	ft_strdel(path);
	if (!(*path = ft_strdups(arg)))
		return (-3);
	len = ft_strlens(*path);
	if (*path[len - 1] != '/')
		*path = ft_strjoinf(*path, "/", 1);
	return (0);
}

char	sh_env_string(char *arg, char **string)
{
	if (!(*string = ft_strdups(arg)))
		return (-4);
	return (1);
}

bool	sh_env_has_verbose(char **argv)
{
	int		i;
	int		j;

	i = 0;
	while (argv[i] && argv[i][0] == '-' && !(argv[i][1] == '-' && !argv[i][2]))
	{
		j = 1;
		while (argv[i][j])
		{
			if ((argv[i][j] == 'S' || argv[i][j] == 'P' || argv[i][j] == 'u')
			&& !argv[i][j + 1])
			{
				i++;
				break ;
			}
			if (argv[i][j] == 'S' || argv[i][j] == 'P' || argv[i][j] == 'u')
				break ;
			if (argv[i][j] == 'v')
				return (TRUE);
			j++;
		}
		i += (argv && argv[i]) ? 1 : 0;
	}
	return (FALSE);
}
