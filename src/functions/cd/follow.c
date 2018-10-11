/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   follow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 23:19:28 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 12:08:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_cd_get_real_path(t_shell *sh, t_env *env, char *param)
{
	char	*path;
	char	*new;

	path = NULL;
	new = param + sh_cd_remove_troll(param);
	if (param[0] == '/')
		return (ft_strdups(param));
	if (param[0] == '\0' && env_search(env, "HOME"))
		return (ft_strdups(env_search(env, "HOME")));
	if (new[0] == '\0')
		return (ft_strdups(sh->prompt.location));
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

char		sh_cd_follow(t_shell *sh, t_env *env, char *value, char dash)
{
	char	*path;
	char	*rpath;
	t_stat	lstats;

	path = sh_cd_get_real_path(sh, env, sh_cd_remove_last_slash(value));
	if (lstat(path, &lstats) < 0)
		return (sh_cd_error(value, path, 1));
	if (!S_ISLNK(lstats.st_mode) && !dash)
		return (sh_cd_nofollow(sh, env, value, path));
	if (!S_ISLNK(lstats.st_mode) && dash)
		return (sh_cd_nofollow_dash(sh, env, value, path));
	if (ft_strcmps(rpath = realpath(path, NULL), path) == 0)
	{
		ft_strdel(&rpath);
		return (sh_cd_error(value, path, 2));
	}
	ft_strdel(&rpath);
	if (chdir(path) == -1)
		return (sh_cd_error(value, path, 3));
	if (env_search(env, "PWD"))
		env_insert(sh, env, "OLDPWD", env_search(env, "PWD"));
	env_insert(sh, env, "PWD", path);
	(dash) ? ft_putendl(path) : 0;
	ft_strdel(&path);
	return (0);
}
