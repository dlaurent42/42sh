/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 16:02:37 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 14:14:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_select_down_cursor(t_shell *sh, int add)
{
	if (!sh->modes.select)
		sh->selection.stop = sh->cursor.abs_pos;
	else if (add)
		sh->selection.stop = sh->cursor.abs_pos;
	else if (sh->cursor.abs_pos > sh->selection.start_abs
	&& sh->cursor.abs_pos < sh->selection.stop)
	{
		sh->selection.start_abs = sh->cursor.abs_pos;
		sh->selection.start_rel = sh->cursor.rel_pos;
	}
	else
	{
		sh->selection.start_abs = sh->selection.stop;
		sh->selection.stop = sh->cursor.abs_pos;
		sh->selection.start_rel = sh_get_start_rel_from_abs(sh);
	}
	sh->modes.select = TRUE;
}

void		sh_select_down(t_shell *sh)
{
	char	add;

	if (sh->cursor.abs_pos == sh->buffer.display_len)
		return ;
	if (!sh->modes.select)
	{
		sh->selection.start_abs = sh->cursor.abs_pos;
		sh->selection.start_rel = sh->cursor.rel_pos;
	}
	add = (sh->modes.select && sh->cursor.abs_pos == sh->selection.stop)
		? TRUE : FALSE;
	sh_move_down(sh);
	sh_select_down_cursor(sh, add);
	sh_select_print(sh);
}
