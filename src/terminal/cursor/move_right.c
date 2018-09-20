/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 00:21:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_move_right(t_shell *sh)
{
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	if ((sh->cursor.y == 0
		&& sh->cursor.x + 2 + sh->prompt.len_mod > sh->window.width)
	|| (sh->cursor.y > 0 && sh->cursor.x + 2 > sh->window.width))
	{
		ft_putstr(K_DOWN);
		ft_putstr(K_COL_0);
		sh->cursor.x = 0;
		sh->cursor.y++;
	}
	else
	{
		ft_putstr(K_RIGHT);
		sh->cursor.x++;
	}
	sh->cursor.abs_pos++;
	sh_set_rel_pos(sh, 1, 1);
}
