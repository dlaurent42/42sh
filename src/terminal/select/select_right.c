/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_right.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 01:47:00 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 21:53:32 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_select_char(t_shell *sh)
{
	if (sh->modes.select == FALSE)
	{
		sh->selection.start_rel = sh->cursor.rel_pos;
		sh->selection.start_abs = sh->cursor.abs_pos;
	}
	sh->modes.select = TRUE;
	ft_putstr(K_DEL);
	ft_putstr(K_LEFT);
	sh->selection.stop = sh->cursor.abs_pos + 1;
	sh_select_print(sh);
	sh_move_right(sh);
}

static void	sh_unselect_char(t_shell *sh)
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
}

void		sh_select_right_char(t_shell *sh)
{
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	if (sh->modes.select && sh->selection.stop == sh->selection.start_abs)
		return (sh_unselect(sh));
	(sh->modes.select && sh->cursor.abs_pos == sh->selection.start_abs)
		? sh_unselect_char(sh)
		: sh_select_char(sh);
}
