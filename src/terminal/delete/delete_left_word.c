/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_left_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:35:28 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 21:21:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_move_cursor(t_shell *sh)
{
	int	x;
	int	y;

	x = sh->cursor.x;
	y = sh->cursor.y;
	sh_move_home(sh);
	ft_putstr(K_DEL_ALL);
	ft_putstr(sh->buffer.content + sh->buffer.ushift);
	sh->cursor.y = (sh->buffer.display_len + sh->prompt.len_mod)
		/ sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->buffer.display_len + sh->prompt.len_mod) % sh->window.width
		: sh->buffer.display_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.rel_pos = sh->buffer.unicode_len;
	sh_move_to_xy(sh, x, y);
}

static void	sh_delete_words(t_shell *sh, int i, int delta)
{
	while (sh->buffer.content[sh->buffer.ushift + i + delta])
	{
		sh->buffer.content[sh->buffer.ushift + i] =
		sh->buffer.content[
			sh->buffer.ushift
			+ i + delta];
		i++;
	}
	while (sh->buffer.content[sh->buffer.ushift + i])
	{
		sh->buffer.content[sh->buffer.ushift + i] = '\0';
		i++;
	}
}

void		sh_delete_previous_word(t_shell *sh)
{
	int		i;
	int		abs_pos_end;
	int		rel_pos_end;

	if (sh->cursor.abs_pos == 0)
		return ;
	while (sh->buffer.content[sh->buffer.ushift + sh->cursor.rel_pos] == ' '
	|| sh->buffer.content[sh->buffer.ushift + sh->cursor.rel_pos] == '\t')
		sh_move_right(sh);
	abs_pos_end = sh->cursor.abs_pos;
	rel_pos_end = sh->cursor.rel_pos;
	sh_move_previous_word(sh);
	i = sh->cursor.rel_pos;
	sh->buffer.display_len = sh->buffer.display_len
		- abs_pos_end + sh->cursor.abs_pos;
	sh->buffer.unicode_len = sh->buffer.unicode_len
		- rel_pos_end + sh->cursor.rel_pos;
	sh_delete_words(sh, i, rel_pos_end - i);
	sh_move_cursor(sh);
}
