/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   follow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 23:19:28 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/29 01:05:49 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_cd_get_real_path(t_shell *sh, char *param)
{
	char	*path;
	char	*new;

	path = NULL;
	new = param + sh_cd_remove_troll(param);
	if (param[0] == '/')
		return (ft_strdup(param));
	if (param[0] == '\0')
		return (ft_strdup(env_search(sh->env, "HOME")));
	if (new[0] == '\0')
		return (ft_strdup(sh->prompt.location));
	if (!(path = ft_strjoins(sh->prompt.location, "/")))
		return (NULL);
	path = ft_strjoinf(path, new, 1);
	path = sh_cd_parse_path(path);
	if (path[0] == '\0')
	{
		ft_strdel(&path);
		return (ft_strdup("/"));
	}
	return (path);
}

char		sh_cd_follow(t_shell *sh, char *value)
{
	char	*path;
	char	*rpath;
	t_stat	lstats;

	path = sh_cd_get_real_path(sh, sh_cd_remove_last_slash(value));
	if (lstat(path, &lstats) < 0)
		return (sh_cd_error(value, path, 1));
	if (!S_ISLNK(lstats.st_mode))
		return (sh_cd_nofollow(sh, value, path));
	rpath = realpath(path, NULL);
	if (ft_strcmps(rpath, path) == 0)
	{
		ft_strdel(&rpath);
		return (sh_cd_error(value, path, 2));
	}
	ft_strdel(&rpath);
	if (chdir(path) == -1)
		return (sh_cd_error(value, path, 3));
	env_insert(sh, sh->env, "OLDPWD", env_search(sh->env, "PWD"));
	env_insert(sh, sh->env, "PWD", path);
	ft_strdel(&path);
	return (0);
}
