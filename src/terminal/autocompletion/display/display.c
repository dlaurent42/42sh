/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:35:50 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:27:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			calculate_offset(t_ac *ac)
{
	int				len;
	float			nbr;
	float			calc;

	len = ac->items_to_display;
	if (len == 1)
		return (1);
	nbr = (float)len / ac->number_of_columns;
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

static bool			bottom_of_screen_is_not_reached(t_ac *ac)
{
	if (ac->number_of_printed_rows
			< (ac->height - ac->shell->cursor.y) - 1)
		return (true);
	return (false);
}

static void			print_display(t_ac *ac, t_args *head, int len)
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
		while (++line_len < ac->number_of_columns)
		{
			if (!(args = get_file_number(head, (prints) + (line_len) * (len))))
				break ;
			if (bottom_of_screen_is_not_reached(ac))
				auto_file_name(ac, args);
			if (last_args)
			{
				last_args->hor_next = args;
				args->hor_prev = last_args;
			}
			last_args = args;
		}
		if (bottom_of_screen_is_not_reached(ac))
		{
			ft_putchar('\n');
			ac->number_of_printed_rows++;
		}
	}
	args = get_file_number(head, 0);
	last_args->hor_next = args;
	args->hor_prev = last_args;
}

void				auto_display(t_ac *ac, t_args *args)
{
	int				x;
	int				y;
	int				rows;

	x = ac->shell->cursor.x;
	y = ac->shell->cursor.y;
	auto_clear_selection_screen(ac);
	ft_putchar('\n');
	ac->number_of_printed_rows = 1;
	print_display(ac, args, calculate_offset(ac));
	rows = ac->number_of_printed_rows;
	if (!(ft_putstr_multi(K_UP, rows)))
	{
		while (rows--)
			ft_putstr(K_UP);
	}
	sh_move_to_xy(ac->shell, x, y);
}
