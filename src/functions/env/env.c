/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:21:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 20:06:39 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	OPTIONS
**		option -i			: empty the env
**		option - 			: same as -i
**		option -u $name		: unset $name
**		option -P $path		: specify path for searching binaries to exec
**		option -S $string	: 
*/

/*
	- make a copy of current env
	- check options
		-> if [-i] or [-] : empty the env
		-> if [-u] : unset env var (no err even if var does not exist)
		-> if [-P]
			-> if no string after then error
			-> else parse folder to get all executables that have execution rights
		-> if [-v] : verbose
		-> if [-S] : parse string, remove escape sequences and add the result as
		environment variable
*/

char		*sh_env_get_string(char *string, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		string = ft_strjoinf(string, argv[i], 1);
		if (argv[i + 1])
			string = ft_strjoinf(string, " ", 1);
		i++;
	}
	return (string);
}

char		sh_env(t_shell *sh, char **argv)
{
	int		i;
	int		res;
	char	*path;
	char	*string;
	t_env	*env;

	i = 0;
	res = 0;
	path = NULL;
	string = NULL;
	env = env_copy(sh);
	sh_debug(NULL, "argv", NULL);
	while (argv && argv[i])
	{
		sh_debug(NULL, ft_strjoins("... ", argv[i]), NULL);
		i++;
	}
	i = 0;
	if (argv)
		if ((i = sh_env_parse(env, &path, &string, argv)) < 0)
			return (sh_env_error(env, path, string, i));
	sh_debug(NULL, ft_itoa(i), NULL);
	string = sh_env_get_string(string, argv + i);
	sh_debug(NULL, string, NULL);
	i = 0;
	res = 0;
	if (ft_strcountif(string, '=') == 0 && string)
		return (sh_env_exec(env, path, string)); // renvoie 0 quoiqu'il arrive ou func res
	ft_strdel(&path);
	return (sh_env_display(sh, env, string));
}
