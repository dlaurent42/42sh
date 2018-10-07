/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:11:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 21:54:20 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_env_parse_return(char **argv, int i, int res)
{
	i += (res >= 0 && argv[i]
	&& argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
		? 1 : 0;
	if (res >= 0)
		return (i + res);
	return (res);
}

static char	sh_env_prepare_u(t_env *env, int *j, int *i, char **argv)
{
	int	k;

	k = *j + 1;
	if (argv[*i][*j + 1] == '\0')
	{
		*i = *i + 1;
		*j = ft_strlens(argv[*i]) - 1;
		if (argv[*i])
			return (sh_env_unset(env, argv[*i]));
		return (-5);
	}
	*j = ft_strlens(argv[*i]) - 1;
	return (sh_env_unset(env, argv[*i] + k));
}

static char	sh_env_prepare_s(char **string, int *j, int *i, char **argv)
{
	int	k;

	k = *j + 1;
	if (argv[*i][*j + 1] == '\0')
	{
		*i = *i + 1;
		*j = ft_strlens(argv[*i]) - 1;
		if (argv[*i])
			return (sh_env_string(argv[*i], string));
		return (-4);
	}
	*j = ft_strlens(argv[*i]) - 1;
	return (sh_env_string(argv[*i] + k, string));
}

static char	sh_env_prepare_p(char **path, int *j, int *i, char **argv)
{
	int	k;

	k = *j + 1;
	if (argv[*i][*j + 1] == '\0')
	{
		*i = *i + 1;
		*j = ft_strlens(argv[*i]) - 1;
		if (argv[*i])
			return (sh_env_path(argv[*i], path));
		return (-3);
	}
	*j = ft_strlens(argv[*i]) - 1;
	return (sh_env_path(argv[*i] + k, path));
}

char		sh_env_parse(t_env *env, char **path, char **string, char **argv)
{
	int		i;
	int		j;
	int		res[2];

	i = 0;
	res[0] = 0;
	res[1] = sh_env_has_verbose(argv);
	while (argv[i] && res[0] == 0
	&& argv[i][0] == '-' && !(argv[i][1] == '-' && !argv[i][2]))
	{
		j = 0;
		while (res[0] == 0 && argv[i][++j])
			if (argv[i][j] == 'i')
				sh_env_empty(env);
			else if (argv[i][j] == 'u')
				res[0] = sh_env_prepare_u(env, &j, &i, argv);
			else if (argv[i][j] == 'P')
				res[0] = sh_env_prepare_p(path, &j, &i, argv);
			else if (argv[i][j] == 'S')
				res[0] = sh_env_prepare_s(string, &j, &i, argv);
			else if (argv[i][j] != 'v' && (res[0] = -99))
				sh_env_error(NULL, NULL, ft_strdups(argv[i] + j), -6);
		i += (argv[i] && res[0] == 0) ? 1 : 0;
	}
	return (sh_env_parse_return(argv, i, res[0]));
}
