/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:35:50 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/04 14:01:56 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			calculate_offset(t_frame *frame)
{
	int				len;
	float			nbr;
	float			calc;

	len = frame->items_to_display;
	if (len == 1)
		return (1);
	nbr = (float)len / frame->number_of_columns;
	calc = nbr - (int)nbr;
	calc *= 10;
	len = (int)calc;
	return (len >= 1 ? (int)nbr + 1 : (int)nbr);
}

static t_args		*get_file_number(t_args *head, int file_number)
{
	while (head)
	{
		if (head->data.file_number == file_number && !head->data.no_file)
			return (head);
		head = head->next;
	}
	return (NULL);
}

static bool			bottom_of_screen_is_not_reached(t_frame *frame)
{
	if (frame->number_of_printed_rows
			< (frame->height - frame->shell->cursor.y) - 1)
		return (true);
	return (false);
}

static void			print_display(t_frame *frame, t_args *head, int len)
{
	int				prints;
	int				line_len;
	t_args			*args;
	t_args			*last_args;

	prints = -1;
	last_args = NULL;
	while (++prints < len)
	{
		line_len = -1;
		while (++line_len < frame->number_of_columns)
		{
			if (!(args = get_file_number(head, (prints) + (line_len) * (len))))
				break ;
			if (bottom_of_screen_is_not_reached(frame))
				auto_file_name(frame, args);
			if (last_args)
			{
				last_args->hor_next = args;
				args->hor_prev = last_args;
			}
			last_args = args;
		}
		if (bottom_of_screen_is_not_reached(frame))
		{
			ft_putchar('\n');
			frame->number_of_printed_rows++;
		}
	}
	args = get_file_number(head, 0);
	last_args->hor_next = args;
	args->hor_prev = last_args;
}

void				auto_display(t_frame *frame, t_args *args)
{
	int				x;
	int				y;
	int				rows;

	x = frame->shell->cursor.x;
	y = frame->shell->cursor.y;
	auto_clear_selection_screen(frame);
	ft_putchar('\n');
	frame->number_of_printed_rows = 1;
	print_display(frame, args, calculate_offset(frame));
	rows = frame->number_of_printed_rows;
	while (rows--)
		ft_putstr(K_UP);
	sh_move_to_xy(frame->shell, x, y);
}
