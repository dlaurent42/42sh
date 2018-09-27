/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_left_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:35:28 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 15:24:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_delete_previous_word(t_shell *sh)
{
	if (sh->cursor.abs_pos == 0)
		return ;
	while (sh->cursor.rel_pos
	&& ((unsigned char)sh->buffer.content[sh->cursor.rel_pos] == ' '
	|| (unsigned char)sh->buffer.content[sh->cursor.rel_pos] == '\t'))
		sh_delete_char(sh);
	while (sh->cursor.rel_pos
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos - 1] != ' '
	&& (unsigned char)sh->buffer.content[sh->cursor.rel_pos - 1] != '\t')
		sh_delete_char(sh);
}
