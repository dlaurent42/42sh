/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_right_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:53:38 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 20:51:59 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		sh_select_char(t_shell *sh)
{
	int	x;

	x = sh->buffer.ushift;
	if (!sh->modes.select)
	{
		sh->selection.start_abs = sh->cursor.abs_pos;
		sh->selection.start_rel = sh->cursor.rel_pos;
	}
	if ((unsigned char)sh->buffer.content[x + sh->cursor.rel_pos + 1] == ' '
	|| (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos + 1] == '\t')
		sh_move_right(sh);
	while (sh->cursor.abs_pos < sh->buffer.display_len
	&& ((unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] == '\t'))
		sh_move_right(sh);
	while (sh->cursor.abs_pos < sh->buffer.display_len
	&& (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos + 1] != ' '
	&& (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos + 1] != '\t')
		sh_move_right(sh);
	sh->selection.stop = sh->cursor.abs_pos;
}

static void		sh_ugly_trick(t_shell *sh)
{
	sh_move_right(sh);
	sh->modes.select = (sh->selection.stop == sh->cursor.abs_pos)
		? FALSE : TRUE;
}

static void		sh_unselect_char(t_shell *sh)
{
	int	x;

	x = sh->buffer.ushift;
	while (sh->cursor.abs_pos < sh->buffer.display_len
	&& (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] != ' '
	&& (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] != '\t')
	{
		sh_ugly_trick(sh);
		if (sh->selection.stop == sh->cursor.abs_pos)
			return (sh_select_char(sh));
	}
	while (sh->cursor.abs_pos < sh->buffer.display_len
	&& ((unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] == '\t'))
	{
		sh_ugly_trick(sh);
		if (sh->selection.stop == sh->cursor.abs_pos)
			return (sh_select_char(sh));
	}
	if (sh->cursor.abs_pos < sh->selection.stop)
	{
		sh->selection.start_rel = sh->cursor.rel_pos;
		sh->selection.start_abs = sh->cursor.abs_pos;
	}
}

void			sh_select_right_word(t_shell *sh)
{
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	(sh->modes.select && sh->cursor.abs_pos == sh->selection.start_abs)
		? sh_unselect_char(sh)
		: sh_select_char(sh);
	sh_select_print(sh);
}
