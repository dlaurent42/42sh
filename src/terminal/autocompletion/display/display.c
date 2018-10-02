/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:35:50 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/02 17:20:43 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			move_up_to_prompt(t_frame *frame)
{
	int				rows;

	rows = frame->number_of_printed_rows;
	while (rows--)
		ft_putstr(K_UP);
}

static void			print_display(t_frame *frame, t_args *args)
{
	int				position_on_row;

	position_on_row = 0;
	if (args)
		frame->number_of_printed_rows = 1;
	else
		frame->number_of_printed_rows = 0;
	while (args && frame->number_of_printed_rows
			< (frame->height - frame->shell->cursor.y) - 1)
	{
		if (!args->data.no_file)
		{
			auto_file_name(frame, args);
			position_on_row++;
			if (position_on_row >= frame->number_of_columns && args->next)
			{
				ft_putchar('\n');
				position_on_row = 0;
				frame->number_of_printed_rows++;
			}
		}
		args = args->next;
	}
}

void				auto_display(t_frame *frame, t_args *args)
{
	int				x;
	int				y;

	x = frame->shell->cursor.x;
	y = frame->shell->cursor.y;
	auto_clear_selection_screen(frame);
	ft_putchar('\n');
	print_display(frame, args);
	move_up_to_prompt(frame);
	sh_move_to_xy(frame->shell, x, y);
}
