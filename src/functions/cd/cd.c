/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:20:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 11:02:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	OPTIONS
**		option -L : Force symbolic links to be followed (default behavior)
**		option -P : Use the physical directory structure without following
**					symbolic links
**
**	EXAMPLES
**		cd link -> repo => link
**		cd -L link -> repo => link
**		cd -P link -> repo => repo
**		cd -L -P link -> repo => repo
*/

static char	sh_cd_dispatch(t_shell *sh, int option_p, char **argv, int current)
{
	if (!argv[current])
		return (sh_cd_nofollow(sh, env_search(sh->env, "HOME"), NULL));
	if (argv[current] && argv[current + 1])
		return (sh_cd_error(argv[current], NULL, 4));
	if (argv[current][0] == '-' && argv[current][1] == '-' && !argv[current][2])
		return (sh_cd_nofollow(sh, env_search(sh->env, "HOME"), NULL));
	if (option_p && argv[current][0] == '-' && !argv[current][1])
		return (sh_cd_nofollow(sh, env_search(sh->env, "OLDPWD"), NULL));
	if (option_p)
		return (sh_cd_nofollow(sh, argv[current], NULL));
	if (argv[current][0] == '-' && !argv[current][1])
		return (sh_cd_follow(sh, env_search(sh->env, "OLDPWD")));
	return (sh_cd_follow(sh, argv[current]));
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
