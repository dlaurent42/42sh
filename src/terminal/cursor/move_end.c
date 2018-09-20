/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 00:22:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_move_end(t_shell *sh)
{
	ft_putstr(K_COL_0);
	sh->cursor.x = 0;
	while (sh->cursor.y <
		(sh->buffer.display_len + sh->prompt.len_mod) / sh->window.width)
	{
		ft_putstr(K_DOWN);
		sh->cursor.y++;
	}
	while ((sh->cursor.y && sh->cursor.x <
		(sh->buffer.display_len + sh->prompt.len_mod) % sh->window.width)
	|| (sh->cursor.y == 0 && sh->cursor.x <
		sh->buffer.display_len + sh->prompt.len_mod))
	{
		ft_putstr(K_RIGHT);
		sh->cursor.x++;
	}
	if (sh->cursor.y == 0)
		sh->cursor.x = sh->buffer.display_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.rel_pos = sh->buffer.unicode_len;
}
