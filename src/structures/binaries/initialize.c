/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:19:03 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/19 20:10:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		bin_parse_folder(t_shell *sh, t_bin *bin, char *path)
{
	DIR			*dir;
	t_stat		stats;
	t_dirent	*dirent;

	if (!(dir = opendir(path)))
		return ;
	while ((dirent = readdir(dir)))
		if (lstat(path, &stats) == 0)
			bin_insert(
				sh,
				bin,
				bin_new_obj(
					sh,
					dirent->d_name,
					path,
					stats));
	closedir(dir);
}

void			bin_initialize(t_shell *sh, t_env *env, t_bin *bin)
{
	int			i;
	char		*path;
	char		**path_list;

	i = 0;
	if (!(path = env_search(env, "PATH")))
		error_no_path_var(sh);
	if (!(path_list = ft_strsplit(path, ':')))
		error_no_path_var(sh);
	while (path_list[i])
	{
		bin_parse_folder(sh, bin, path_list[i]);
		ft_strdel(&path_list[i]);
		i++;
	}
	free(path_list);
}
