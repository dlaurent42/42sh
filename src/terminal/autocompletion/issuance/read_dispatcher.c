/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:23:53 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/05 13:26:54 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			auto_arrows_dispatcher(t_frame *frame)
{
	char			*line;

	line = frame->shell->read->line;
	frame->del_file_name = frame->select->data.str;
	if (line[2] == 65 || line[2] == 90)
		auto_move_up(frame);
	else if (line[2] == 66 || line[0] == 9)
		auto_move_down(frame);
	else if (line[2] == 67)
		auto_move_right(frame);
	else if (line[2] == 68)
		auto_move_left(frame);
}

void				auto_read_dispatcher(t_frame *frame)
{
	t_shell			*shell;
	char			*line;

	shell = frame->shell;
	line = frame->shell->read->line;
	if (line[0] == 9 || (line[0] == 27 && line[1] == 91))
		auto_arrows_dispatcher(frame);
	else
	{
		if (sh_is_delete_combination(line))
			sh_deletion_dispatcher(frame->shell);
		else if (line[0] == 10)
			auto_manage_buffer(frame->shell,
					(frame->select->data.dir) ? "/" : " ");
		else
			sh_fill_buffer(shell);
		auto_clear_selection_screen(frame);
		frame->shell->modes.auto_completion = 0;
	}
}
