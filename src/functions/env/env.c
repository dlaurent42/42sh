/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:21:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 14:24:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Display, set, or remove environment variables, Run a command in a modified
** environment.
**
** -----------------------------------------------------------------------------
**
** Syntax
**       env [OPTION]... [NAME=VALUE]... [COMMAND [ARGS]...]
**
** Options
**
**    -u NAME   Remove variable NAME from the environment, if it was in the
**              environment.
**
**   -/-i       Start with an empty environment, ignoring the inherited
**        		environment.
**
** Arguments of the form `VARIABLE=VALUE' set the environment variable VARIABLE
** to value VALUE.
**
** VALUE can be empty (`VARIABLE='). Setting a variable to an empty value is
** different from unsetting it.
**
** The first remaining argument specifies the program name to invoke; it is
** searched for according to the `PATH' environment variable. Any remaining
** arguments are passed as arguments to that program.
**
** If no command name is specified following the environment specifications,
** the resulting environment is printed. This is like specifying a command name
** of `printenv'.
**
** Options added :
**   -v        		verbose
**   -P utilpath    specify path for exec
**	 -S string		stringsplit
*/

static char	**sh_env_get_string(char *string, char **argv)
{
	int		i;
	int		j;
	char	**arr;
	char	**split;

	i = 0;
	j = 0;
	split = ft_strsplit(string, ' ');
	ft_strdel(&string);
	if (!(arr = (char **)ft_memalloc(sizeof(char *) * (
	ft_count_argv((void **)argv) + ft_count_argv((void **)split) + 1))))
		return (NULL);
	while (split && split[i])
	{
		arr[i] = ft_strdupf(split[i]);
		i++;
	}
	(split) ? free(split) : 0;
	while (argv && argv[j])
	{
		arr[i + j] = ft_strdups(argv[j]);
		j++;
	}
	arr[i + j] = 0;
	return (arr);
}

static void	sh_env_del_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_strdel(&arr[i]);
		i++;
	}
	(arr) ? free(arr) : 0;
}

char		sh_env(t_shell *sh, t_env *src, char **argv)
{
	int		res;
	char	*path;
	char	*string;
	char	**arr;
	t_env	*env;

	res = 0;
	path = NULL;
	string = NULL;
	env = env_copy(sh, src);
	if (argv)
		if ((res = sh_env_parse(env, &path, &string, argv)) < 0)
			return (sh_env_error(env, path, string, res));
	arr = sh_env_get_string(string, argv + res);
	res = sh_env_display(sh, env, arr, sh_env_has_verbose(argv));
	if (res < 0)
	{
		res = sh_env_exec(env, path, arr - res, sh_env_has_verbose(argv));
		sh_env_del_arr(arr);
	}
	ft_strdel(&path);
	return (res);
}
