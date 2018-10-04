/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_prev_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 00:40:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 20:45:24 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_move_previous_word(t_shell *sh)
{
	int	x;
	int	current_position;

	x = sh->buffer.ushift;
	current_position = sh->cursor.abs_pos;
	if (sh->cursor.abs_pos == 0)
		return ;
	if (sh->cursor.rel_pos
	&& ((unsigned char)sh->buffer.content[x + sh->cursor.rel_pos - 1] == ' '
	|| (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos - 1] == '\t'))
		sh_move_left(sh);
	while (((unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] == '\t')
	&& sh->cursor.abs_pos != 0)
		sh_move_left(sh);
	while ((unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] != ' '
	&& (unsigned char)sh->buffer.content[x + sh->cursor.rel_pos] != '\t'
	&& sh->cursor.rel_pos)
		sh_move_left(sh);
	if (current_position != sh->cursor.abs_pos && sh->cursor.abs_pos)
		sh_move_right(sh);
}
