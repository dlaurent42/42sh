/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unselect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:11:20 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 17:32:21 by dlaurent         ###   ########.fr       */
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
	sh_move_home(sh);
	sh_move_y(sh, y);
	sh_move_x(sh, x);
	sh_set_rel_pos(sh, sh->cursor.abs_pos, 1);
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
	ft_printf("%s ",
		sh->buffer.content
		+ sh->buffer.ushift
		+ sh->cursor.rel_pos);
	sh_unselect_reset_pos(sh, x, y);
	sh->selection.stop = -1;
	sh->selection.start_abs = -1;
	sh->selection.start_rel = -1;
}

void		sh_unselect_delete(t_shell *sh, unsigned char c)
{
	int	stop;
	int	start;

	stop = sh->selection.stop;
	start = sh->selection.start_abs;
	if (sh->modes.select == FALSE)
		return ;
	if ((!ft_isprint(c) && c != 16 && c < 0b10000000)
	|| (c >= 0b10000000 && c < 0b11000000)
	|| c == 11)
		return (sh_unselect(sh));
	while (sh->cursor.abs_pos < stop)
		sh_move_right(sh);
	while (sh->cursor.abs_pos > start)
		sh_delete_char(sh);
	sh->modes.select = FALSE;
}
