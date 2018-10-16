/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 23:54:43 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 23:55:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_cd_tilde_handler(t_shell *sh, t_env *env, char *s)
{
	char	res;
	char	*home;
	char	*path;

	if (!(home = env_search(env, "HOME")))
		return (sh_cd_error(NULL, NULL, 5));
	if (!(path = ft_strjoins(home, s + 1)))
		return (sh_cd_error(NULL, NULL, 5));
	res = sh_cd_follow(sh, env, path, FALSE);
	ft_strdel(&path);
	return (res);
}

char		sh_cd_dispatch(t_shell *sh, t_env *env, char **argv, int i)
{
	char	res;

	res = 0;
	if (!argv[i] || (argv[i][0] == '~' && !argv[i][1]))
		res = (env_search(env, "HOME"))
			? sh_cd_nofollow(sh, env, env_search(env, "HOME"), NULL)
			: sh_cd_error(NULL, NULL, 5);
	else if (argv[i][0] == '~')
		res = sh_cd_tilde_handler(sh, env, argv[i]);
	else if (argv[i][0] == '-' && !argv[i][1] && env_search(env, "OLDPWD"))
		res = sh_cd_follow(sh, env, env_search(env, "OLDPWD"), TRUE);
	else if (argv[i][0] == '-' && !argv[i][1])
		res = sh_cd_error(NULL, NULL, 6);
	else if (argv[i] && argv[i + 1])
		res = sh_cd_error(argv[i], NULL, 4);
	else
		res = sh_cd_follow(sh, env, argv[i], FALSE);
	return (res);
}

static char	sh_cd_tilde_handler_p(t_shell *sh, t_env *env, char *s)
{
	char	res;
	char	*home;
	char	*path;

	if (!(home = env_search(env, "HOME")))
		return (sh_cd_error(NULL, NULL, 5));
	if (!(path = ft_strjoins(home, s + 1)))
		return (sh_cd_error(NULL, NULL, 5));
	res = sh_cd_nofollow(sh, env, path, NULL);
	ft_strdel(&path);
	return (res);
}

char		sh_cd_dispatch_p(t_shell *sh, t_env *env, char **argv, int i)
{
	char	res;

	res = 0;
	if (!argv[i] || (argv[i][0] == '~' && !argv[i][1]))
		res = (env_search(env, "HOME"))
			? sh_cd_nofollow(sh, env, env_search(env, "HOME"), NULL)
			: sh_cd_error(NULL, NULL, 5);
	else if (argv[i][0] == '~')
		res = sh_cd_tilde_handler_p(sh, env, argv[i]);
	else if (argv[i][0] == '-' && !argv[i][1] && env_search(env, "OLDPWD"))
		res = sh_cd_nofollow_dash(sh, env, env_search(env, "OLDPWD"), NULL);
	else if (argv[i][0] == '-' && !argv[i][1])
		res = sh_cd_error(NULL, NULL, 6);
	else if (argv[i] && argv[i + 1])
		res = sh_cd_error(argv[i], NULL, 4);
	else
		res = sh_cd_nofollow(sh, env, argv[i], NULL);
	return (res);
}
