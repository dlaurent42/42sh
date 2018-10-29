/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:35:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/27 09:38:53 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			calculate_offset(t_shell *sh)
{
	int				len;
	float			nbr;
	float			calc;

	len = sh->ac->items_to_display;
	if (len == 1)
		return (1);
	nbr = (float)len / sh->ac->number_of_columns;
	calc = nbr - (int)nbr;
	calc *= 10;
	len = (int)calc;
	if (!(int)nbr)
		return (1);
	return (len >= 1 ? (int)nbr + 1 : (int)nbr);
}

static t_obj		*get_file_number(t_obj *head, int file_number)
{
	while (head)
	{
		if (head->data.file_number == file_number && !head->data.no_file)
			return (head);
		head = head->next;
	}
	return (NULL);
}

static bool			bottom_of_screen_is_not_reached(t_shell *sh, bool new_row)
{
	if (sh->ac->number_of_printed_rows
			< (sh->ac->height - sh->cursor.y) - 1)
	{
		if (new_row)
		{
			ft_putchar('\n');
			sh->ac->number_of_printed_rows++;
		}
		return (true);
	}
	return (false);
}

static void			print_display(t_shell *sh, t_obj *head, int len)
{
	int				prints;
	int				line_len;
	t_obj			*obj;
	t_obj			*last_obj;

	prints = -1;
	last_obj = NULL;
	while (++prints < len)
	{
		line_len = -1;
		while (++line_len < sh->ac->number_of_columns)
		{
			if (!(obj = get_file_number(head, (prints) + (line_len) * (len))))
				break ;
			if (bottom_of_screen_is_not_reached(sh, false))
				auto_file_name(sh, obj);
			(last_obj) ? last_obj->hor_next = obj : 0;
			obj->hor_prev = last_obj;
			last_obj = obj;
		}
		bottom_of_screen_is_not_reached(sh, true);
	}
	obj = get_file_number(head, 0);
	last_obj->hor_next = obj;
	obj->hor_prev = last_obj;
}

void				auto_display(t_shell *sh, t_obj *obj, bool first_print)
{
	int				x;
	int				y;
	int				rows;

	auto_calculate_number_of_columns(sh);
	x = sh->cursor.x;
	y = sh->cursor.y;
	if (!first_print)
		auto_clear_selection_screen(sh);
	if (sh->cursor.x != 0)
		ft_putchar('\n');
	sh->ac->number_of_printed_rows = 1;
	print_display(sh, obj, calculate_offset(sh));
	rows = sh->ac->number_of_printed_rows;
	if (!(ft_putstr_multi(K_UP, rows)))
	{
		while (rows--)
			ft_putstr(K_UP);
	}
	sh_move_to_xy(sh, x, y);
	sh->ac->window_resize = obj;
}
