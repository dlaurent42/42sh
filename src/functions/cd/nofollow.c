/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nofollow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 23:11:37 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 13:49:25 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_cd_get_real_path(t_shell *sh, char *param)
{
	char	*path;
	char	*rpath;

	path = NULL;
	rpath = NULL;
	if (param[0] == '/')
		return (realpath(param, NULL));
	if (param[0] == '\0')
		return (ft_strdup(env_search(sh->env, "HOME")));
	if (!(path = ft_strjoins(sh->prompt.location, "/")))
		return (NULL);
	path = ft_strjoinf(path, param, 1);
	rpath = realpath(path, NULL);
	ft_strdel(&path);
	return (rpath);
}

char		sh_cd_nofollow(t_shell *sh, char *value, char *path, char dash)
{
	char	*rpath;
	t_stat	lstats;

	rpath = (path) ? path : sh_cd_get_real_path(sh, value);
	if (lstat(rpath, &lstats) < 0)
		return (sh_cd_error(value, rpath, 1));
	if (chdir(rpath) == -1)
		return (sh_cd_error(value, rpath, 3));
	env_insert(sh, sh->env, "OLDPWD", env_search(sh->env, "PWD"));
	env_insert(sh, sh->env, "PWD", rpath);
	(dash) ? ft_putendl(rpath) : 0;
	ft_strdel(&rpath);
	return (0);
}
