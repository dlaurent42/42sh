/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 12:47:00 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 12:10:52 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			read_directory(t_read_dir *read_dir)
{
	if (((ft_strcmp(read_dir->file->d_name, ".")
					&& ft_strcmp(read_dir->file->d_name, "..")))
			|| (read_dir->file->d_name[0] == '.')
			|| (read_dir->file->d_name[0] != '.'))
	{
		if (!(read_dir->tmp = auto_create_obj()))
		{
			auto_free_obj(&read_dir->head);
			return (false);
		}
		if (!auto_path(read_dir->tmp, read_dir->obj->data.parent_path,
				read_dir->file->d_name))
		{
			free(read_dir->tmp);
			return (false);
		}
		if (!read_dir->head)
			read_dir->head = read_dir->tmp;
		else
			read_dir->last_obj->next = read_dir->tmp;
		read_dir->last_obj = read_dir->tmp;
	}
	return (true);
}

static t_obj		*get_directory_contents(t_obj *obj)
{
	t_read_dir		read_dir;

	read_dir.obj = obj;
	read_dir.head = NULL;
	if (!(read_dir.directory = opendir(read_dir.obj->data.parent_path)))
		return (NULL);
	while ((read_dir.file = readdir(read_dir.directory)))
	{
		if (!read_directory(&read_dir))
		{
			auto_free_obj(&read_dir.head);
			closedir(read_dir.directory);
			return (NULL);
		}
	}
	closedir(read_dir.directory);
	return (read_dir.head);
}

void				auto_do_ls(t_shell *sh, t_obj *obj)
{
	t_obj			*head;

	if (!(head = get_directory_contents(obj)))
		return ;
	sh->ac->current_obj = head;
	auto_get_attributes(sh);
	head = sh->ac->current_obj;
	auto_show_screen(sh, head);
	auto_free_obj(&head);
}
