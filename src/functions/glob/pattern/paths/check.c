/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:02:43 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/22 14:28:52 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_glob_check_existence(
	char *name, char *str, t_filesystem *fs1)
{
	if (name[0] == '.' && (str[0] != '.' || ft_strcmps(name, ".") == 0 || ft_strcmps(name, "..") == 0))
		return (FALSE);
	if (glob_match(name, str, fs1->lst))
	{
		ft_printf("......... sh_glob_check_existence : TRUE\n");
		return (TRUE);
	}
	ft_printf("......... sh_glob_check_existence : FALSE\n");
	return (FALSE);
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
		ft_printf(".... sh_glob_check_paths checking path : %s\n", path->path);
		if ((dir = opendir(path->path)))
			while ((dirent = readdir(dir)))
			{
				ft_printf("...... sh_glob_check_paths %s\n", dirent->d_name);
				if ((dirent->d_type == DT_DIR || dirent->d_type == DT_LNK)
				&& sh_glob_check_existence(dirent->d_name, str, fs1))
					sh_glob_add_path(fs2, path->path, dirent->d_name);
			}
		(dir) ? closedir(dir) : 0;
		path = path->next;
	}
}

void		sh_glob_check_final_paths(t_glob *glob, t_filesystem *fs1, char *str)
{
	t_path		*path;
	DIR			*dir;
	t_dirent	*dirent;

	path = fs1->paths;
	while (path)
	{
		ft_printf(".... sh_glob_check_final_path checking path : %s\n", path->path);
		if ((dir = opendir(path->path)))
			while ((dirent = readdir(dir)))
			{
				ft_printf("...... sh_glob_check_final_paths %s\n", dirent->d_name);
				if (sh_glob_check_existence(dirent->d_name, str, fs1))
				{
					sh_glob_add_result(glob, path->path, dirent->d_name);
					ft_printf("...... sh_glob_check_final_paths add as result %s\n", dirent->d_name);
				}
			}
		(dir) ? closedir(dir) : 0;
		path = path->next;
	}
}

static void	sh_glob_recursive_all_paths(t_glob *glob, char *path, t_filesystem *fs2)
{
	DIR			*dir;
	t_dirent	*dirent;
	char		*next_path;

	next_path = NULL;
	if ((dir = opendir(path)))
		while ((dirent = readdir(dir)))
		{
			if ((dirent->d_type == DT_DIR || dirent->d_type == DT_LNK)
			&& ft_strcmps(dirent->d_name, ".") & ft_strcmps(dirent->d_name, ".."))
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

void		sh_glob_check_all_paths(t_glob *glob, t_filesystem *fs1, t_filesystem *fs2)
{
	t_path		*path;

	(void)glob;
	path = fs1->paths;
	while (path)
	{
		ft_printf(".... sh_glob_check_all_paths checking path : %s\n", path->path);
		sh_glob_recursive_all_paths(glob, ft_strdups(path->path), fs2);
		path = path->next;
	}
}
