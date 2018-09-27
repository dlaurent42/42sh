/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_right_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:53:38 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/24 19:56:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		sh_select_char(t_shell *sh)
{
	if ((unsigned char)sh->buffer.content[sh->cursor.rel_pos + 1] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos + 1] == '\t')
		sh_select_right_char(sh);
	while (sh->cursor.abs_pos < sh->buffer.display_len
	&& ((unsigned char)sh->buffer.content[sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos] == '\t'))
		sh_select_right_char(sh);
	while (sh->cursor.abs_pos < sh->buffer.display_len
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos + 1] != ' '
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos + 1] != '\t')
		sh_select_right_char(sh);
}

static void		sh_unselect_char(t_shell *sh)
{
	while (sh->cursor.abs_pos < sh->buffer.display_len
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos] != ' '
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos] != '\t')
		if (sh->selection.start_abs == sh->selection.stop)
			return (sh_select_char(sh));
		else
			sh_select_right_char(sh);
	while (sh->cursor.abs_pos < sh->buffer.display_len
	&& ((unsigned char)sh->buffer.content[sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos] == '\t'))
		if (sh->selection.start_abs == sh->selection.stop)
			return (sh_select_char(sh));
		else
			sh_select_right_char(sh);
}

void			sh_select_right_word(t_shell *sh)
{
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	(sh->modes.select && sh->cursor.abs_pos == sh->selection.start_abs)
		? sh_unselect_char(sh)
		: sh_select_char(sh);
}
