/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:20:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 11:53:06 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_cd_dispatch(t_shell *sh, int option_p, char **argv, int i)
{
	char	res;

	res = 0;
	if (!argv[i] || (argv[i][0] == '~' && !argv[i][1])
	|| (argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2]))
		res = (env_search(sh->env, "HOME"))
			? sh_cd_nofollow(sh, env_search(sh->env, "HOME"), NULL, FALSE)
			: sh_cd_error(NULL, NULL, 5);
	else if (argv[i] && argv[i + 1])
		res = sh_cd_error(argv[i], NULL, 5);
	else if (argv[i][0] == '-' && !argv[i][1] && env_search(sh->env, "OLDPWD"))
		res = (option_p)
			? sh_cd_nofollow(sh, env_search(sh->env, "OLDPWD"), NULL, TRUE)
			: sh_cd_follow(sh, env_search(sh->env, "OLDPWD"), TRUE);
	else if (argv[i][0] == '-' && !argv[i][1])
		res = sh_cd_error(argv[i], NULL, 6);
	else 
		res = (option_p)
			? sh_cd_nofollow(sh, argv[i], NULL, FALSE)
			: sh_cd_follow(sh, argv[i], FALSE);
	return (res);
}

char		sh_cd(t_shell *sh, char **argv)
{
	int		current;
	char	option_p;
	char	option_l;
	size_t	argc;

	current = 0;
	option_l = 0;
	option_p = 0;
	argc = ft_count_argv((void **)argv);
	while (argv[current] && argv[current][0] == '-')
	{
		if (argv[current][1] == 'L' && !argv[current][2])
			option_l = TRUE;
		else if (argv[current][1] == 'P' && !argv[current][2])
			option_p = TRUE;
		else
			break ;
		current++;
	}
	return (sh_cd_dispatch(sh, option_p, argv, current));
}
