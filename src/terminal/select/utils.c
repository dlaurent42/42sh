/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:47:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 20:53:16 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_select_set_pos(t_shell *sh)
{
	int	x;
	int	y;

	x = sh->cursor.x;
	y = sh->cursor.y;
	sh->cursor.rel_pos = sh->buffer.unicode_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.y = (sh->cursor.abs_pos + sh->prompt.len_mod) / sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->cursor.abs_pos + sh->prompt.len_mod) % sh->window.width
		: sh->cursor.abs_pos;
	sh_move_to_xy(sh, x, y);
}

int			sh_get_selection_len(t_shell *sh)
{
	int	x;
	int	len;
	int	abs_i;
	int	rel_i;

	len = 0;
	x = sh->buffer.ushift;
	abs_i = sh->selection.start_abs;
	rel_i = sh->selection.start_rel;
	while (abs_i < sh->selection.stop)
	{
		len += ((unsigned char)sh->buffer.content[x + rel_i] >= 0b11110000)
			? 1 : 0;
		len += ((unsigned char)sh->buffer.content[x + rel_i] >= 0b11100000)
			? 1 : 0;
		len += ((unsigned char)sh->buffer.content[x + rel_i] >= 0b11000000)
			? 2 : 0;
		len += ((unsigned char)sh->buffer.content[x + rel_i] < 0b10000000)
			? 1 : 0;
		if ((unsigned char)sh->buffer.content[x + rel_i] >= 0b11000000
		|| (unsigned char)sh->buffer.content[x + rel_i] < 0b10000000)
			abs_i++;
		rel_i++;
	}
	return (len);
}

int			sh_get_start_rel_from_abs(t_shell *sh)
{
	int	x;
	int	abs_i;
	int	rel;

	abs_i = 0;
	rel = 0;
	x = sh->buffer.ushift;
	while (sh->buffer.content[x + rel] && abs_i <= sh->selection.start_abs)
	{
		if ((unsigned char)sh->buffer.content[x + rel] >= 0b11000000
		|| (unsigned char)sh->buffer.content[x + rel] < 0b10000000)
			abs_i++;
		rel++;
	}
	rel += ((unsigned char)sh->buffer.content[x + rel] >= 0b11110000) ? 1 : 0;
	rel += ((unsigned char)sh->buffer.content[x + rel] >= 0b11100000) ? 1 : 0;
	rel += ((unsigned char)sh->buffer.content[x + rel] >= 0b11000000) ? 1 : 0;
	return (rel);
}
