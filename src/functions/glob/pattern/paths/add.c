/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 10:32:48 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/22 14:40:39 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_glob_add_initial_path(t_glob *glob)
{
	t_path	*new;

	if (!(new = (void *)ft_memalloc(sizeof(t_path))))
		return ;
	new->path = (glob->starts_by_path)
		? ft_strdups("/")
		: ft_strjoinf(getcwd(new->path, PATH_MAX), "/", 1);
	glob->fs[0]->paths = new;
}

void	sh_glob_add_path(t_filesystem *fs, char *path, char *name)
{
	t_path	*new;

	if (!(new = (t_path *)ft_memalloc(sizeof(t_path))))
		return ;
	new->path = (path && path[ft_strlen(path) - 1] != '/')
		? ft_strjoins(path, "/")
		: ft_strdups(path);
	new->path = ft_strjoinf(new->path, name, 1);
	ft_printf("......... sh_glob_add_path %s\n", new->path);
	new->next = (fs && fs->paths) ? fs->paths : NULL;
	fs->paths = new;
}

void	sh_glob_add_result(t_glob *glob, char *path, char *name)
{
	char	*result;
	char	*curr_path;

	curr_path = NULL;
	result = ft_strjoins(path, "/");
	result = ft_strjoinf(result, name, 1);
	if (glob->ends_by_path)
		result = ft_strjoinf(result, "/", 1);
	(glob->result) ? glob->result = ft_strjoinf(glob->result, " ", 1) : 0;
	if (!glob->starts_by_path)
	{
		curr_path = getcwd(curr_path, PATH_MAX);
		glob->result = ft_strjoinf(glob->result, result + ft_strlens(curr_path) + 1, 1);
		ft_strdel(&curr_path);
		ft_strdel(&result);
	}
	else
		glob->result = ft_strjoinf(glob->result, result, 3);
}
