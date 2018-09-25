/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 14:46:15 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/25 16:03:51 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_move_up(t_shell *sh)
{
	if ((sh->cursor.y == 1 && sh->cursor.x < sh->prompt.len_mod)
	|| sh->cursor.y == 0)
		return (sh_move_home(sh));
	ft_putstr(K_UP);
	sh->cursor.abs_pos -= sh->window.width;
	sh->cursor.y--;
	if (sh->cursor.y == 0)
		sh->cursor.x -= sh->prompt.len_mod;
	sh_set_rel_pos(sh, sh->window.width, -1);
}
