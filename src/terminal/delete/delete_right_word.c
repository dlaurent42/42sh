/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_right_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:35:55 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 15:24:18 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_delete_next_word(t_shell *sh)
{
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	while (sh->cursor.abs_pos < sh->buffer.display_len
	&& ((unsigned char)sh->buffer.content[sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos] == '\t'))
		sh_delete_current_char(sh);
	while (sh->cursor.abs_pos < sh->buffer.display_len
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos] != ' '
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos] != '\t')
		sh_delete_current_char(sh);
}
