/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:35:50 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 00:53:28 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int			calculate_offset(t_shell *shell)
{
	int				len;
	float			nbr;
	float			calc;

	len = shell->ac->items_to_display;
	if (len == 1)
		return (1);
	nbr = (float)len / shell->ac->number_of_columns;
	calc = nbr - (int)nbr;
	calc *= 10;
	len = (int)calc;
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

static bool			bottom_of_screen_is_not_reached(t_shell *shell)
{
	if (shell->ac->number_of_printed_rows
			< (shell->ac->height - shell->cursor.y) - 1)
		return (true);
	return (false);
}

static void			print_display(t_shell *shell, t_obj *head, int len)
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
		while (++line_len < shell->ac->number_of_columns)
		{
			if (!(obj = get_file_number(head, (prints) + (line_len) * (len))))
				break ;
			if (bottom_of_screen_is_not_reached(shell))
				auto_file_name(shell, obj);
			if (last_obj)
			{
				last_obj->hor_next = obj;
				obj->hor_prev = last_obj;
			}
			last_obj = obj;
		}
		if (bottom_of_screen_is_not_reached(shell))
		{
			ft_putchar('\n');
			shell->ac->number_of_printed_rows++;
		}
	}
	obj = get_file_number(head, 0);
	last_obj->hor_next = obj;
	obj->hor_prev = last_obj;
}

void				auto_display(t_shell *shell, t_obj *obj)
{
	int				x;
	int				y;
	int				rows;

	x = shell->cursor.x;
	y = shell->cursor.y;
	auto_clear_selection_screen(shell);
	ft_putchar('\n');
	shell->ac->number_of_printed_rows = 1;
	print_display(shell, obj, calculate_offset(shell));
	rows = shell->ac->number_of_printed_rows;
	if (!(ft_putstr_multi(K_UP, rows)))
	{
		while (rows--)
			ft_putstr(K_UP);
	}
	sh_move_to_xy(shell, x, y);
	shell->ac->window_resize = obj;
}
