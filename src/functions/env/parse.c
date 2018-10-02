/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:11:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 20:01:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_env_empty(t_env *env)
{
	size_t		i;
	t_env_item	*item;

	i = 0;
	sh_debug(NULL, "... empty", NULL);
	sh_debug(NULL, ft_itoa(env->count), NULL);
	if (!env)
		return ;
	while (i < env->size)
	{
		item = env->items[i];
		if (item && item != &env->del)
			env_delete_specified_item(item);
		i++;
	}
	i = 0;
	while (env->environment[i])
	{
		ft_strdel(&env->environment[i]);
		i++;
	}
	env->count = 0;
}

static char	sh_env_unset(t_env *env, char *arg)
{
	char	*arg_parsed;

	sh_debug(NULL, "... unset", NULL);
	if (ft_strcountif(arg, '='))
		return (-1);
	if (!(arg_parsed = sh_unsetenv_parse(ft_strdups(arg))))
		return (-2);
	env_delete_item(env, arg_parsed);
	ft_strdel(&arg_parsed);
	return (0);
}

static char	sh_env_path(char *arg, char **path)
{
	sh_debug(NULL, "... path", NULL);
	size_t	len;
	ft_strdel(path);
	if (!(*path = ft_strdups(arg)))
		return (-3);
	len = ft_strlens(*path);
	if (*path[len - 1] != '/')
		*path = ft_strjoinf(*path, "/", 1);
	return (0);
}

static char	sh_env_string(char *arg, char **string)
{
	sh_debug(NULL, "... string", NULL);
	if (!(*string = ft_strdups(arg)))
		return (-4);
	return (1);
}

char		sh_env_parse(t_env *env, char **path, char **string, char **argv)
{
	int		i;
	char	res;

	i = 0;
	res = 0;
	sh_debug(NULL, "parsing", NULL);
	while (argv[i] && res == 0)
	{
		if (argv[i][0] == '-' 
		&& ((argv[i][1] == 'i' && !argv[i][2]) || !argv[i][1]))
			sh_env_empty(env);
		else if (argv[i][0] == '-' && argv[i][1] == 'u' && !argv[i][2])
			res = sh_env_unset(env, *(argv + ++i));
		else if (argv[i][0] == '-' && argv[i][1] == 'P' && !argv[i][2])
			res = sh_env_path(*(argv + ++i), path);
		else if (argv[i][0] == '-' && argv[i][1] == 'S' && !argv[i][2])
			res = sh_env_string(*(argv + ++i), string);
		else
			break ;
		i += (argv[i]) ? 1 : 0;
	}
	if (res >= 0)
		return (i + res);
	return (res);
}
