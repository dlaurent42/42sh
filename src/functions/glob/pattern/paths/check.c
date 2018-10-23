/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:02:43 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/23 11:27:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_glob_check_existence(
	char *name, char *str, t_filesystem *fs1)
{
	if (name[0] == '.' && (str[0] != '.'
	|| ft_strcmps(name, ".") == 0 || ft_strcmps(name, "..") == 0))
		return (FALSE);
	return (glob_match(name, str, fs1->lst));
}

void		sh_glob_check_paths(
	t_glob *glob, t_filesystem *fs1, char *str, t_filesystem *fs2)
{
	t_path		*path;
	DIR			*dir;
	t_dirent	*dirent;

	(void)glob;
	path = fs1->paths;
	while (path)
	{
		if ((dir = opendir(path->path)))
			while ((dirent = readdir(dir)))
				if ((dirent->d_type == DT_DIR || dirent->d_type == DT_LNK)
				&& sh_glob_check_existence(dirent->d_name, str, fs1))
					sh_glob_add_path(fs2, path->path, dirent->d_name);
		(dir) ? closedir(dir) : 0;
		path = path->next;
	}
}

void		sh_glob_check_final_paths(
	t_glob *glob, t_filesystem *fs1, char *str)
{
	t_path		*path;
	DIR			*dir;
	t_dirent	*dirent;

	path = fs1->paths;
	while (path)
	{
		if ((dir = opendir(path->path)))
			while ((dirent = readdir(dir)))
			{
				if (((glob->ends_by_path && dirent->d_type == DT_DIR)
				|| !glob->ends_by_path)
				&& sh_glob_check_existence(dirent->d_name, str, fs1))
					sh_glob_add_result(glob, path->path, dirent->d_name);
			}
		(dir) ? closedir(dir) : 0;
		path = path->next;
	}
}

static void	sh_glob_recursive_all_paths(
	t_glob *glob, char *path, t_filesystem *fs2)
{
	DIR			*dir;
	t_dirent	*dirent;
	char		*next_path;

	next_path = NULL;
	if ((dir = opendir(path)))
		while ((dirent = readdir(dir)))
		{
			if ((dirent->d_type == DT_DIR || dirent->d_type == DT_LNK)
			&& dirent->d_name[0] != '.')
			{
				next_path = ft_strjoins(path, "/");
				next_path = ft_strjoinf(next_path, dirent->d_name, 1);
				sh_glob_recursive_all_paths(glob, next_path, fs2);
				(fs2)
					? sh_glob_add_path(fs2, path, dirent->d_name)
					: sh_glob_add_result(glob, path, dirent->d_name);
			}
		}
	(dir) ? closedir(dir) : 0;
	ft_strdel(&path);
}

void		sh_glob_check_all_paths(
	t_glob *glob, t_filesystem *fs1, t_filesystem *fs2)
{
	t_path		*path;

	(void)glob;
	path = fs1->paths;
	while (path)
	{
		(fs2)
			? sh_glob_add_path(fs2, path->path, NULL)
			: sh_glob_add_result(glob, path->path, NULL);
		sh_glob_recursive_all_paths(glob, ft_strdups(path->path), fs2);
		path = path->next;
	}
}
