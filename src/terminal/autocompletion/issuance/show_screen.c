/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:03:57 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/04 11:26:54 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			delete_str(t_frame *frame)
{
	int				len;

	len = ft_strlenu(frame->del_file_name);
	while (len--)
		sh_delete_char(frame->shell);
}

static void			fill_buffer_with_wild(t_frame *frame, t_args *args)
{
	frame->del_file_name = frame->args->data.path;
	delete_str(frame);
	while (args)
	{
		if (!args->data.no_file && *args->data.str != '.')
		{
			auto_manage_buffer(frame, args->data.path);
			auto_manage_buffer(frame, " ");
		}
		args = args->next;
	}
}

static void			do_loop(t_frame *frame, t_args *head)
{
	t_args			*args;

	args = head;
	while (frame->shell->modes.auto_completion)
	{
		if (!auto_calculate_number_of_columns(frame))
			break ;
		args = head;
		delete_str(frame);
		auto_manage_buffer(frame, frame->select->data.str);
		if (frame->select->ver_next == frame->select)
		{
			auto_manage_buffer(frame, (frame->select->data.dir) ? "/" : " ");
			break ;
		}
		auto_display(frame, args);
		read(0, frame->shell->read->line, 4);
		if (frame->shell->read->line[0] == 4)
			break ;
		auto_read_dispatcher(frame);
		ft_bzero(frame->shell->read->line, LINE_SIZE);
	}
}

void				auto_show_screen(t_frame *frame, t_args *args)
{
	auto_do_file_admin(frame, args);
	if (frame->cmp_mode == MODE_NON)
		return ;
	frame->del_file_name = frame->file_name;
	if (frame->auto_mode == AUTO_WILD)
		fill_buffer_with_wild(frame, args);
	else
		do_loop(frame, args);
}
