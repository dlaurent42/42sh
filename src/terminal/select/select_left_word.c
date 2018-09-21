/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_left_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:52:21 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 04:11:26 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_select_left_word(t_shell *sh)
{
	if (sh->cursor.abs_pos == 0)
		return ;
	if ((unsigned char)sh->buffer.content[sh->cursor.rel_pos - 1] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos - 1] == '\t')
		sh_select_left_char(sh);
	while (sh->cursor.rel_pos
	&& ((unsigned char)sh->buffer.content[sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos] == '\t'))
		sh_select_left_char(sh);
	while (sh->cursor.rel_pos
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos - 1] != ' '
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos - 1] != '\t')
		sh_select_left_char(sh);
}
