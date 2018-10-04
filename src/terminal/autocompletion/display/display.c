/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:35:50 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/04 13:14:33 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			calculate_offset(float nbr)
{
	int				ret;
	float			calc;

	calc = nbr - (int)nbr;
	calc *= 10;
	ret = (int)calc;
	return (ret >= 1 ? (int)nbr + 1 : (int)nbr);
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

static void			print_display(t_frame *frame, t_args *head)
{
	int				i;
	int				j;
	int				len;
	int				file_number;
	t_args			*args;
	t_args			*last_args;

	last_args = NULL;
	frame->number_of_printed_rows = 1;
	i = 0;
	len = frame->items_to_display;
	if (len != 1)
		len = calculate_offset((float)len / frame->number_of_columns);
	while (i++ < len)
	{
		j = 0;
		while (j++ < frame->number_of_columns)
		{
			file_number = (i - 1) + (j - 1) * (len);
			args = get_file_number(head, file_number);
			if (!args)
				break ;
			if (bottom_of_screen_is_not_reached(frame))
				auto_file_name(frame, args);
			if (last_args)
			{
				last_args->hor_next = args;
				args->hor_prev = last_args;
			}
			if (args)
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
	print_display(frame, args);
	rows = frame->number_of_printed_rows;
	while (rows--)
		ft_putstr(K_UP);
	sh_move_to_xy(frame->shell, x, y);
}
