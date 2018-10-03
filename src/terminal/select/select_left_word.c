/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_left_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:52:21 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 22:02:09 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		sh_select_char(t_shell *sh)
{
	(!sh->modes.select) ? sh->selection.stop = sh->cursor.abs_pos : 0;
	sh->modes.select = TRUE;
	if ((unsigned char)sh->buffer.content[sh->cursor.rel_pos - 1] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos - 1] == '\t')
	{
		sh_move_left(sh);
		ft_printf("%s%s", K_DEL, K_LEFT);
	}
	while (sh->cursor.rel_pos
	&& ((unsigned char)sh->buffer.content[sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos] == '\t'))
	{
		sh_move_left(sh);
		ft_printf("%s%s", K_DEL, K_LEFT);
	}
	while (sh->cursor.rel_pos
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos - 1] != ' '
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos - 1] != '\t')
	{
		sh_move_left(sh);
		ft_printf("%s%s", K_DEL, K_LEFT);
	}
	sh->selection.start_rel = sh->cursor.rel_pos;
	sh->selection.start_abs = sh->cursor.abs_pos;
	sh_select_print(sh);
}

static void		sh_unselect_char(t_shell *sh)
{
	while (sh->cursor.rel_pos
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos] != ' '
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos] != '\t')
	{
		sh_move_left(sh);
		ft_printf("%s%s", K_DEL, K_LEFT);
	}
	while (sh->cursor.rel_pos
	&& ((unsigned char)sh->buffer.content[sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos] == '\t'))
	{
		sh_move_left(sh);
		ft_printf("%s%s", K_DEL, K_LEFT);
	}
	sh->selection.stop = sh->cursor.abs_pos;
	if (sh->selection.stop < sh->selection.start_abs)
	{
		sh->selection.stop = sh->selection.start_abs;
		sh->selection.start_abs = sh->cursor.abs_pos;
		sh->selection.start_rel = sh->cursor.rel_pos;
	}
	sh_select_print(sh);
}

void			sh_select_left_word(t_shell *sh)
{
	if (sh->cursor.abs_pos == 0)
		return ;
	(sh->modes.select && sh->cursor.abs_pos == sh->selection.stop)
		? sh_unselect_char(sh)
		: sh_select_char(sh);
}
