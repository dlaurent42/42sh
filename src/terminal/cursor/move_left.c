/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 16:10:07 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_move_left(t_shell *sh)
{
	unsigned char	i;

	i = 0;
	if (sh->cursor.abs_pos == 0)
		return ;
	if (sh->cursor.x > 0)
	{
		ft_putstr(K_LEFT);
		sh->cursor.x--;
	}
	else
	{
		ft_putstr(K_UP);
		sh->cursor.y--;
		sh->cursor.x = (sh->cursor.y == 0)
		? sh->window.width - sh->prompt.len_mod - 1
		: sh->window.width - 1;
		ft_putstr_multi(K_RIGHT, sh->window.width - 1);
	}
	sh->cursor.abs_pos--;
	sh_set_rel_pos(sh, 1, -1);
}
