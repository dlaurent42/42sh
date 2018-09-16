/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_valid_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:03:57 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/14 23:54:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

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
		do_loop(frame, args, &position_on_row);
		if (position_on_row)
			ft_putchar('\n');
		move_right(frame);
		usleep(100000);//DELETE
	}
}
