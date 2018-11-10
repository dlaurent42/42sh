/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   follow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 23:19:28 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 20:58:56 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_cd_get_real_path(t_shell *sh, t_env *env, char *param)
{
	char	*path;
	char	*new;
	char	*cdpath;

	path = NULL;
	new = param + sh_cd_remove_troll(param);
	if (new[0] == '/')
		return (realpath(param, NULL));
	if (new[0] == '\0' && env_search(env, "HOME"))
		return (ft_strdups(env_search(env, "HOME")));
	if (new[0] == '\0')
		return (ft_strdups(sh->prompt.location));
	if ((cdpath = env_search(env, "CDPATH")) && cdpath[0] && new[0] != '.')
		return (sh_cd_handle_cdpath(env, new));
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

static char	*sh_cd_get_real_path_pwd(t_shell *sh, t_env *env, char *param)
{
	char	*new;
	char	*cdpath;

	(void)sh;
	new = ft_strjoins("/", param + sh_cd_remove_troll(param));
	cdpath = env_search(env, "CDPATH");
	new = (cdpath && cdpath[0])
		? ft_strjoinf(cdpath, new, 2)
		: ft_strjoinf(env_search(env, "PWD"), new, 2);
	new = sh_cd_parse_path(new);
	if (new[0] == '\0' || new[0] == '.')
	{
		ft_strdel(&new);
		new = ft_strdups("/");
	}
	return (new);
}

static void	sh_cd_follow_insert_env(t_shell *sh, t_env *env, char *path)
{
	char	*rpath;

	rpath = NULL;
	(path[0] != '/') ? rpath = ft_strjoins("/", path) : 0;
	if ((env_search(env, "OLDPWD") || env->count + 1 < env->size)
	&& env_search(env, "PWD"))
		env_insert(sh, env, "OLDPWD", env_search(env, "PWD"));
	if (env_search(env, "PWD") || env->count + 1 < env->size)
		env_insert(sh, env, "PWD", rpath);
	ft_strdel(&rpath);
}

static char	sh_cd_follow_del_and_return(
	char *rpath, char *value, char *path, char status)
{
	ft_strdel(&rpath);
	return (sh_cd_error(value, path, status));
}

char		sh_cd_follow(t_shell *sh, t_env *env, char *value, char dash)
{
	char	*path;
	char	*rpath;
	t_stat	lstats;

	path = (value && value[0] != '/' && env_search(env, "PWD"))
		? sh_cd_get_real_path_pwd(sh, env, sh_cd_remove_last_slash(value))
		: sh_cd_get_real_path(sh, env, sh_cd_remove_last_slash(value));
	if (ft_strlens(path) >= PATH_MAX)
		return (sh_cd_error(value, path, 7));
	if (!path || access(path, F_OK) == -1 || lstat(path, &lstats) == -1)
		return (sh_cd_error(value, path, 1));
	if (!S_ISLNK(lstats.st_mode) && !dash)
		return (sh_cd_nofollow(sh, env, value, path));
	if (!S_ISLNK(lstats.st_mode) && dash)
		return (sh_cd_nofollow_dash(sh, env, value, path));
	if (ft_strcmps(rpath = realpath(path, NULL), path) == 0)
		return (sh_cd_follow_del_and_return(rpath, value, path, 2));
	ft_strdel(&rpath);
	if (chdir(path) == -1)
		return (sh_cd_error(value, path, 3));
	sh_cd_follow_insert_env(sh, env, path);
	(dash) ? ft_putendl(path) : 0;
	ft_strdel(&path);
	return (0);
}
