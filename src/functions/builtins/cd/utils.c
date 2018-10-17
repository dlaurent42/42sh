/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 22:47:09 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 11:14:29 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_cd_replace_dbl_slash(char *s)
{
	int			i;
	int			j;

	i = 0;
	while (s[i + 1])
	{
		if (s[i] == '/' && s[i + 1] == '/')
		{
			j = i + 1;
			while (s[j + 1])
			{
				s[j] = s[j + 1];
				j++;
			}
			s[j] = '\0';
		}
		i++;
	}
	return (s);
}

static char	*sh_cd_replace_tilde(t_env *env, char *path)
{
	char		*s;
	t_passwd	*pw;

	pw = getpwuid(getuid());
	s = (env_search(env, "HOME"))
		? ft_strdups(env_search(env, "HOME"))
		: ft_strdups(pw->pw_dir);
	if (ft_strlens(path) > 1)
		s = ft_strjoinf(s, path + 1, 1);
	ft_strdel(&path);
	return (s);
}

char		*sh_cd_handle_cdpath(t_env *env, char *rel_path)
{
	int		i;
	char	*path;
	char	**split;

	i = -1;
	path = NULL;
	if (!(split = ft_strsplit(env_search(env, "CDPATH"), ':')))
		return (rel_path);
	while (split[++i])
	{
		if (split[i][0] == '~')
			split[i] = sh_cd_replace_tilde(env, split[i]);
		path = ft_strjoinf(ft_strjoins(split[i], "/"), rel_path, 1);
		if (access(path, F_OK) != -1)
		{
			ft_putendl(sh_cd_replace_dbl_slash(path));
			break ;
		}
		ft_strdel(&path);
	}
	i = -1;
	while (split[++i])
		ft_strdel(&split[i]);
	free(split);
	return (path);
}
