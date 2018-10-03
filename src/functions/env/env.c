/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:21:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 11:40:34 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	if (argv)
		if ((i = sh_env_parse(env, &path, &string, argv)) < 0)
			return (sh_env_error(env, path, string, i));
	string = sh_env_get_string(string, argv + i);
	if (ft_strcountif(string, '=') == 0 && string)
		return (sh_env_exec(env, path, string));
	ft_strdel(&path);
	return (sh_env_display(sh, env, string));
}
