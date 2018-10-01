/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:29:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/29 19:50:44 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_delete_all(t_shell *sh)
{
	sh_move_end(sh);
	if ((sh->buffer.display_len + sh->prompt.len)
	/ sh->window.width + 1 > sh->window.height)
	{
		ft_putstr(CLEAR_SCREEN);
		sh_print_prompt(sh);
		bzero(sh->buffer.content, sh->buffer.unicode_len);
		sh->buffer.unicode_len = 0;
		sh->buffer.display_len = 0;
		sh->cursor.abs_pos = 0;
		sh->cursor.rel_pos = 0;
		sh->cursor.x = 0;
		sh->cursor.y = 0;
	}
	else
		while (sh->cursor.abs_pos)
			sh_delete_char(sh);
}
