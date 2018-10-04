/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_left_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:52:21 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 20:54:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		sh_select_char(t_shell *sh)
{
	int	x;

	x = sh->buffer.ushift;
	(!sh->modes.select) ? sh->selection.stop = sh->cursor.abs_pos : 0;
	if ((unsigned char)sh->buffer.content[x + sh->cursor.rel_pos - 1] == ' '
	|| (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos - 1] == '\t')
		sh_move_left(sh);
	while (sh->cursor.rel_pos
	&& ((unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] == '\t'))
		sh_move_left(sh);
	while (sh->cursor.rel_pos
	&& (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos - 1] != ' '
	&& (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos - 1] != '\t')
		sh_move_left(sh);
	sh->selection.start_rel = sh->cursor.rel_pos;
	sh->selection.start_abs = sh->cursor.abs_pos;
}

static void		sh_unselect_check(t_shell *sh)
{
	if ((sh->selection.stop = sh->cursor.abs_pos) < sh->selection.start_abs)
	{
		sh->selection.stop = sh->selection.start_abs;
		sh->selection.start_abs = sh->cursor.abs_pos;
		sh->selection.start_rel = sh->cursor.rel_pos;
	}
}

static void		sh_unselect_char(t_shell *sh)
{
	int	x;

	x = sh->buffer.ushift;
	while (sh->cursor.rel_pos
	&& (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] != ' '
	&& (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] != '\t')
	{
		sh_move_left(sh);
		sh->modes.select = (sh->selection.start_abs == sh->cursor.abs_pos)
			? FALSE : TRUE;
		if (sh->selection.start_abs == sh->cursor.abs_pos)
			return (sh_select_char(sh));
	}
	while (sh->cursor.rel_pos
	&& ((unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] == '\t'))
	{
		sh_move_left(sh);
		sh->modes.select = (sh->selection.start_abs == sh->cursor.abs_pos)
			? FALSE : TRUE;
		if (sh->selection.start_abs == sh->cursor.abs_pos)
			return (sh_select_char(sh));
	}
	sh_unselect_check(sh);
}

void			sh_select_left_word(t_shell *sh)
{
	if (sh->cursor.abs_pos == 0)
		return ;
	(sh->modes.select && sh->cursor.abs_pos == sh->selection.stop)
		? sh_unselect_char(sh)
		: sh_select_char(sh);
	sh_select_print(sh);
}
