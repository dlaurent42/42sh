/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nofollow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 23:11:37 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/29 01:02:44 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_cd_get_real_path(t_shell *sh, char *param)
{
	char	*path;
	char	*rpath;

	path = NULL;
	if (param[0] == '/')
		return (ft_strdup(param));
	if (param[0] == '\0')
		return (ft_strdup(env_search(sh->env, "HOME")));
	if (!(path = ft_strjoins(sh->prompt.location, "/")))
		return (NULL);
	path = ft_strjoinf(path, param, 1);
	rpath = realpath(path, NULL);
	ft_strdel(&path);
	return (rpath);
}

char		sh_cd_nofollow(t_shell *sh, char *value, char *given_path)
{
	char	*path;
	t_stat	lstats;

	path = (given_path) ? given_path : sh_cd_get_real_path(sh, value);
	if (lstat(path, &lstats) < 0)
		return (sh_cd_error(value, path, 1));
	if (chdir(path) == -1)
		return (sh_cd_error(value, path, 3));
	env_insert(sh, sh->env, "OLDPWD", env_search(sh->env, "PWD"));
	env_insert(sh, sh->env, "PWD", path);
	ft_strdel(&path);
	return (0);
}
