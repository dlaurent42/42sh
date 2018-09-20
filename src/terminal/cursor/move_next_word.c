/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_next_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 00:39:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 00:58:18 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_move_next_word(t_shell *sh)
{
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	while ((unsigned char)sh->buffer.content[sh->cursor.rel_pos] != ' '
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos] != '\t'
	&& sh->cursor.abs_pos < sh->buffer.display_len)
		sh_move_right(sh);
	while (((unsigned char)sh->buffer.content[sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos] == '\t')
	&& sh->cursor.abs_pos < sh->buffer.display_len)
		sh_move_right(sh);
}
