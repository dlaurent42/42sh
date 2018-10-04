/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_right_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:35:55 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 19:09:11 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_move_cursor(t_shell *sh, int pos)
{
	int	x;
	int	y;

	y = (pos + sh->prompt.len_mod) / sh->window.width;
	x = (y) ? (pos + sh->prompt.len_mod) % sh->window.width : pos;
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
	sh->buffer.display_len = ft_strlenu(sh->buffer.content + sh->buffer.ushift);
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content + sh->buffer.ushift);
	sh_move_to_xy(sh, x, y);
}

static void	sh_delete_words(t_shell *sh, int rel_start, int rel_stop)
{
	int	i;

	i = 0;
	while (sh->buffer.content[sh->buffer.ushift + rel_stop + i])
	{
		sh->buffer.content[sh->buffer.ushift + rel_start] =
		sh->buffer.content[sh->buffer.ushift + rel_stop + i];
		rel_start++;
		i++;
	}
	while (sh->buffer.content[sh->buffer.ushift + rel_start])
	{
		sh->buffer.content[sh->buffer.ushift + rel_start] = '\0';
		rel_start++;
	}
}

void		sh_delete_next_word(t_shell *sh)
{
	int		abs_start;
	int		rel_start;
	int		abs_stop;
	int		rel_stop;

	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	abs_start = sh->cursor.abs_pos;
	rel_start = sh->cursor.rel_pos;
	sh_move_next_word(sh);
	abs_stop = sh->cursor.abs_pos;
	rel_stop = sh->cursor.rel_pos;
	sh->buffer.display_len = sh->buffer.display_len
		- abs_stop + abs_start;
	sh->buffer.unicode_len = sh->buffer.unicode_len
		- rel_stop + rel_start;
	sh_delete_words(sh, rel_start, rel_stop);
	sh_move_cursor(sh, abs_start);
}
