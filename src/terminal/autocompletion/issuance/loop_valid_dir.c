/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_valid_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:03:57 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/27 12:13:43 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			do_loop(t_frame *frame, t_args *args, int *position_on_row)
{
	while (args)
	{
		if (!args->data.no_file)
		{
			display(frame, args);
			*position_on_row += 1;
			if (*position_on_row >= frame->number_of_columns)
			{
				ft_putchar('\n');
				*position_on_row = 0;
			}
		}
		args = args->next;
	}
}

////Refactor to the below comment line

static void	sh_arrows_dispatcher(t_frame *frame)
{
	if (frame->shell->read->line[2] == 65)
		move_up(frame);
	else if (frame->shell->read->line[2] == 66)
		move_down(frame);
	else if (frame->shell->read->line[2] == 67)
		move_right(frame);
	else if (frame->shell->read->line[2] == 68)
		move_left(frame);
	else if (frame->shell->read->line[2] == 70)
		ft_printf("end ");
	else if (frame->shell->read->line[2] == 72)
		ft_printf("home ");
}

static void	sh_read_dispatcher(t_frame *frame)
{
	t_shell			*shell;

	shell = frame->shell;
	if (shell->read->line[0] == 27 && shell->read->line[1] == 91)
		sh_arrows_dispatcher(frame);
	else if (shell->read->line[0] == 127)
		sh_read_delete(shell);
	else if (shell->read->line[0] == 9)
		sh_read_autocompletion(shell);
	else
		sh_fill_buffer(shell);
}
////

void				loop_valid_dir(t_frame *frame, t_args *head)
{
	t_args			*args;
	int				position_on_row;

	args = head;
	do_file_admin(frame, args);
	while (1)
	{
		position_on_row = 0;
		ft_putstr("\x1b[H\x1b[2J");//DELETE
		calculate_number_of_columns(frame);
		args = head;
		sh_replace_buffer(frame->shell, frame->select->data.str);
		ft_printf("%s %s\n",
				(char *)frame->shell->prompt.content,
				(char *)frame->shell->buffer.content
				);
		do_loop(frame, args, &position_on_row);
		if (position_on_row)
			ft_putchar('\n');
		//sh_print_prompt(frame->shell);
		read(0, frame->shell->read->line, 4);
		if (frame->shell->read->line[0] == 4)
			break ;
		sh_read_dispatcher(frame);
		bzero(frame->shell->read->line, 5);
	}
}
