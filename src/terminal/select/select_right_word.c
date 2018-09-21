/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_right_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:53:38 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 04:38:46 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_select_right_word(t_shell *sh)
{
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
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
