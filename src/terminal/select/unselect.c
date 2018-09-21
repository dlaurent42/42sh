/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unselect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:11:20 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 04:54:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_unselect_reset_pos(t_shell *sh, int x, int y)
{
	sh->cursor.rel_pos = sh->buffer.unicode_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.y = (sh->cursor.abs_pos + sh->prompt.len_mod) / sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->cursor.abs_pos + sh->prompt.len_mod) % sh->window.width
		: sh->cursor.abs_pos;
	sh_move_to_xy(sh, x, y);
}

static void	sh_unselect_move_to_start(t_shell *sh)
{
	int	x;
	int	y;

	y = (sh->selection.start_abs + sh->prompt.len_mod) / sh->window.width;
	x = (y)
		? (sh->selection.start_abs + sh->prompt.len_mod) % sh->window.width
		: sh->selection.start_abs;
	sh_move_to_xy(sh, x, y);
}

void		sh_unselect(t_shell *sh)
{
	int	x;
	int	y;

	if (sh->modes.select == FALSE)
		return ;
	sh->modes.select = FALSE;
	x = sh->cursor.x;
	y = sh->cursor.y;
	sh_unselect_move_to_start(sh);
	ft_printf("%s ", sh->buffer.content + sh->cursor.rel_pos);
	sh_unselect_reset_pos(sh, x, y);
	sh->selection.stop = -1;
	sh->selection.start_abs = -1;
	sh->selection.start_rel = -1;
}
