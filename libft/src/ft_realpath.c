/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:30:52 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/30 15:12:38 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/stat.h>

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
	if ((S_IFLNK & type) == S_IFLNK)
	{
		if ((len = readlink(*path, sym_path, RL_BUFSIZE)) == -1)
			return (false);
		sym_path[len] = '\0';
		ft_strdel(path);
		if (!(*path = ft_strdups(sym_path)))
			return (false);
	}
	return (true);
}
