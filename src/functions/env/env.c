/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:21:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 22:21:40 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		**sh_env_get_string(char *string, char **argv)
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

char		sh_env_is_exec_mode(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcountif(arr[i], '='))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char		sh_env(t_shell *sh, char **argv)
{
	int		res[2];
	char	*path;
	char	*string;
	char	**arr;
	t_env	*env;

	res[0] = 0;
	res[1] = 0;
	path = NULL;
	string = NULL;
	env = env_copy(sh);
	if (argv)
		if ((res[0] = sh_env_parse(env, &path, &string, argv)) < 0)
			return (sh_env_error(env, path, string, res[0]));
	arr = sh_env_get_string(string, argv + res[0]);
	ft_putstr(arr[0]);
	if (arr && arr[0] && ft_strcountif(arr[0], '=') == 0)
		return (sh_env_exec(env, path, arr));
	ft_strdel(&path);
	return (sh_env_display(sh, env, arr));
}
