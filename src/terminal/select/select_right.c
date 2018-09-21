/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 01:47:00 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 05:41:16 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static unsigned char	sh_assess_stop_pos(t_shell *sh)
{
	unsigned char	c;

	c = sh->buffer.content[sh->cursor.rel_pos];
	if (c >= 0b11110000)
		return (4);
	if (c >= 0b11100000)
		return (3);
	if (c >= 0b11000000)
		return (2);
	return (1);
}

static void				sh_select_char(t_shell *sh)
{
	if (sh->modes.select == FALSE)
	{
		sh->selection.start_rel = sh->cursor.rel_pos;
		sh->selection.start_abs = sh->cursor.abs_pos;
	}
	sh->modes.select = TRUE;
	ft_putstr(K_DEL);
	ft_putstr(K_LEFT);
	sh->selection.stop = sh->cursor.rel_pos + sh_assess_stop_pos(sh);
	sh_select_print(sh);
	sh_select_set_pos(sh);
	sh_move_right(sh);
}

static void				sh_unselect_char(t_shell *sh)
{
	int	curr_stop;

	curr_stop = sh->selection.stop;
	sh_unselect(sh);
	sh_move_right(sh);
	sh->modes.select = TRUE;
	sh->selection.stop = curr_stop;
	sh->selection.start_abs = sh->cursor.abs_pos;
	sh->selection.start_rel = sh->cursor.rel_pos;
	sh_select_print(sh);
	sh_select_set_pos(sh);
}

void					sh_select_right_char(t_shell *sh)
{
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	if (sh->modes.select && sh->selection.stop == sh->selection.start_abs)
		return (sh_unselect(sh));
	(sh->modes.select && sh->cursor.abs_pos == sh->selection.start_abs)
		? sh_unselect_char(sh)
		: sh_select_char(sh);
}
