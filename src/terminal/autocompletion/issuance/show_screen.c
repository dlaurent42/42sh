/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:03:57 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 00:39:12 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			delete_str(t_shell *shell)
{
	int				len;

	len = ft_strlenu(shell->ac->del_file_name);
	while (len--)
		sh_delete_char(shell);
}

static void			fill_buffer_with_wild(t_shell *shell, t_obj *obj)
{
	shell->ac->del_file_name = shell->ac->obj->data.path;
	delete_str(shell);
	while (obj)
	{
		if (!obj->data.no_file && *obj->data.str != '.')
		{
			auto_manage_buffer(shell, obj->data.path);
			auto_manage_buffer(shell, " ");
		}
		obj = obj->next;
	}
}

static void			do_loop(t_shell *shell, t_obj *head)
{
	t_obj			*obj;

	obj = head;
	while (shell->modes.auto_completion)
	{
		if (!auto_calculate_number_of_columns(shell))
			break ;
		obj = head;
		delete_str(shell);
		auto_manage_buffer(shell, shell->ac->select->data.str);
		if (shell->ac->select->ver_next == shell->ac->select)
		{
			auto_manage_buffer(shell, (shell->ac->select->data.dir) ? "/" : " ");
			break ;
		}
		auto_display(shell, obj);
		read(0, shell->read->line, 4);
		if (shell->read->line[0] == 4)
			break ;
		auto_read_dispatcher(shell);
		ft_bzero(shell->read->line, LINE_SIZE);
	}
}

void				auto_show_screen(t_shell *shell, t_obj *obj)
{
	auto_do_file_admin(shell, obj);
	if (shell->ac->cmp_mode == MODE_NON)
		return ;
	shell->ac->del_file_name = shell->ac->file_name;
	if (shell->ac->auto_mode == AUTO_WILD)
		fill_buffer_with_wild(shell, obj);
	else
		do_loop(shell, obj);
}
