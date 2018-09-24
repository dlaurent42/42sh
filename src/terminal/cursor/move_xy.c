/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_xy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/24 19:54:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_move_y(t_shell *sh, int y)
{
	while (sh->cursor.y < y)
	{
		ft_putstr(K_DOWN);
		sh->cursor.y++;
		sh->cursor.x = sh->prompt.len_mod;
		sh->cursor.abs_pos += sh->window.width;
	}
}

void	sh_move_x(t_shell *sh, int x)
{
	while (sh->cursor.x != x)
	{
		sh->cursor.x > x
			? ft_putstr(K_LEFT)
			: ft_putstr(K_RIGHT);
		sh->cursor.abs_pos += (sh->cursor.x > x)
			? (-1)
			: 1;
		sh->cursor.x += (sh->cursor.x > x)
			? (-1)
			: 1;
	}
}

void	sh_move_to_xy(t_shell *sh, int x, int y)
{
	sh->cursor.y -= (sh->cursor.x == 0 && sh->cursor.y) ? 1 : 0;
	sh_move_home(sh);
	sh_move_y(sh, y);
	sh_move_x(sh, x);
	sh_set_rel_pos(sh, sh->cursor.abs_pos, 1);
}
