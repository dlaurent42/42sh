/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:20:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 20:10:28 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_cd_tilde_handler(t_shell *sh, char *s, int option_p)
{
	char	res;
	char	*home;
	char	*path;

	if (!(home = env_search(sh->env, "HOME")))
		return (sh_cd_error(NULL, NULL, 5));
	if (!(path = ft_strjoins(home, s + 1)))
		return (sh_cd_error(NULL, NULL, 5));
	res = (option_p)
		? sh_cd_nofollow(sh, path, NULL, FALSE)
		: sh_cd_follow(sh, path, FALSE);
	ft_strdel(&path);
	return (res);
}

static char	sh_cd_dispatch(t_shell *sh, int option_p, char **argv, int i)
{
	char	res;

	res = 0;
	if (ft_count_argv((void **)argv + i) > 1)
		res = sh_cd_error(NULL, NULL, 7);
	else if (!argv[i] || (argv[i][0] == '~' && !argv[i][1]))
		res = (env_search(sh->env, "HOME"))
			? sh_cd_nofollow(sh, env_search(sh->env, "HOME"), NULL, FALSE)
			: sh_cd_error(NULL, NULL, 5);
	else if (argv[i][0] == '~')
		res = sh_cd_tilde_handler(sh, argv[i], option_p);
	else if (argv[i][0] == '-' && !argv[i][1] && env_search(sh->env, "OLDPWD"))
		res = (option_p)
			? sh_cd_nofollow(sh, env_search(sh->env, "OLDPWD"), NULL, TRUE)
			: sh_cd_follow(sh, env_search(sh->env, "OLDPWD"), TRUE);
	else if (argv[i][0] == '-' && !argv[i][1])
		res = sh_cd_error(NULL, NULL, 6);
	else if (argv[i] && argv[i + 1])
		res = sh_cd_error(argv[i], NULL, 7);
	else
		res = (option_p)
			? sh_cd_nofollow(sh, argv[i], NULL, FALSE)
			: sh_cd_follow(sh, argv[i], FALSE);
	return (res);
}

char		sh_cd(t_shell *sh, char **argv)
{
	int		current;
	bool	option_p;
	bool	option_l;
	size_t	argc;

	current = 0;
	option_l = FALSE;
	option_p = FALSE;
	argc = ft_count_argv((void **)argv);
	current = sh_cd_options(argv, &option_l, &option_p);
	return (sh_cd_dispatch(sh, option_p, argv, current));
}
