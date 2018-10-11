/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_from_filename.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 21:41:03 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 22:22:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_get_path_from_filename(char *filename)
{
	char	*path;
	size_t	path_len;

	path = NULL;
	if (!filename)
		return (NULL);
	if (filename[0] == '/')
		return (ft_strdups(filename));
	if (!(path = getcwd(path, PATH_MAX)))
		return (NULL);
	path_len = ft_strlens(path);
	if (path[path_len - 1] != '/')
		path = ft_strjoinf(path, "/", 1);
	path = ft_strjoinf(path, filename, 1);
	return (path);
}
