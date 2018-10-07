/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 12:47:00 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:27:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <sys/stat.h>

static bool			read_directory(t_read_dir *read_dir)
{
	if (((ft_strcmp(read_dir->file->d_name, ".")
					&& ft_strcmp(read_dir->file->d_name, "..")))
			|| (read_dir->file->d_name[0] == '.')
			|| (read_dir->file->d_name[0] != '.'))
	{
		if (!(read_dir->tmp = auto_create_args()))
		{
			auto_free_args(&read_dir->head);
			return (false);
		}
		if (!auto_path(read_dir->tmp, read_dir->args->data.parent_path,
				read_dir->file->d_name))
		{
			free(read_dir->tmp);
			return (false);
		}
		if (!read_dir->head)
			read_dir->head = read_dir->tmp;
		else
			read_dir->last_args->next = read_dir->tmp;
		read_dir->last_args = read_dir->tmp;
	}
	return (true);
}

static t_args		*get_directory_contents(t_args *args)
{
	t_read_dir		read_dir;

	read_dir.args = args;
	read_dir.head = NULL;
	if (!(read_dir.directory = opendir(read_dir.args->data.parent_path)))
	{
		ft_printf("ft_ls: %s: Permission denied\n", read_dir.args->data.str);
		return (NULL);
	}
	while ((read_dir.file = readdir(read_dir.directory)))
	{
		if (!read_directory(&read_dir))
		{
			auto_free_args(&read_dir.head);
			closedir(read_dir.directory);
			return (NULL);
		}
	}
	closedir(read_dir.directory);
	return (read_dir.head);
}

void				auto_do_ls(t_ac *ac, t_args *args)
{
	t_args			*head;

	if (!(head = get_directory_contents(args)))
		return ;
	ac->current_args = head;
	auto_get_attributes(ac);
	auto_sort(ac);
	head = ac->current_args;
	auto_show_screen(ac, head);
	auto_free_args(&head);
}
