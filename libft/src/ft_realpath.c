/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:30:52 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/10 12:55:56 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>

static char			*ft_replace_dot_slash(char *path)
{
	char	*new;

	new = NULL;
	if (!path || path[0] != '.' || path[1] != '/')
		return (path);
	if (!(new = getcwd(new, PATH_MAX)))
		return (path);
	if (!(new = ft_strjoinf(new, path + 1, 1)))
		return (path);
	ft_strdel(&path);
	return (new);
}

bool				ft_realpath(char **path)
{
	int				len;
	mode_t			type;
	struct stat		stat;
	char			sym_path[RL_BUFSIZE + 1];

	if (access(*path, X_OK) == -1)
		return (false);
	if (lstat(*path, &stat))
		return (false);
	type = stat.st_mode;
	if (S_ISDIR(type))
		return (false);
	if ((S_IFLNK & type) == S_IFLNK)
	{
		if ((len = readlink(*path, sym_path, RL_BUFSIZE)) == -1)
			return (false);
		sym_path[len] = '\0';
		ft_strdel(path);
		if (!(*path = ft_strdups(sym_path)))
			return (false);
	}
	*path = ft_replace_dot_slash(*path);
	return (true);
}
