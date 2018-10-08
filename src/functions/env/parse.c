/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 15:11:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/08 10:51:39 by dlaurent         ###   ########.fr       */
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

char		sh_env_parse(t_env *env, char **path, char **str, char **argv)
{
	int		i;
	int		j;
	int		res;
	bool	verbose;

	i = 0;
	res = 0;
	verbose = sh_env_has_verbose(argv);
	while ((j = 0) == 0 && argv[i] && res == 0
	&& argv[i][0] == '-' && !(argv[i][1] == '-' && !argv[i][2]))
	{
		while (res == 0 && argv[i][++j])
			if (argv[i][j] == 'i' || argv[i][j] == '-')
				sh_env_empty(env, verbose);
			else if (argv[i][j] == 'u')
				res = sh_env_unset(env,
					sh_env_prepare_u(&j, &i, argv), verbose);
			else if (argv[i][j] == 'P')
				res = sh_env_prepare_p(path, &j, &i, argv);
			else if (argv[i][j] == 'S')
				res = sh_env_prepare_s(str, &j, &i, argv);
			else if (argv[i][j] != 'v' && (res = -99))
				sh_env_error(NULL, NULL, ft_strdups(argv[i] + j), -6);
		i += (argv[i] && res == 0) ? 1 : 0;
	}
	return (sh_env_parse_return(argv, i, res));
}
