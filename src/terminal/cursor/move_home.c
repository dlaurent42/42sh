/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_home.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/19 21:46:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_move_home(t_shell *sh)
{
	while (sh->cursor.y)
	{
		ft_putstr(K_UP);
		sh->cursor.y--;
	}
	ft_putstr(K_COL_0);
	sh->cursor.x = 0;
	while (sh->cursor.x < sh->prompt.len_mod)
	{
		ft_putstr(K_RIGHT);
		sh->cursor.x++;
	}
	sh->cursor.x = 0;
	sh->cursor.y = 0;
	sh->cursor.abs_pos = 0;
	sh->cursor.rel_pos = 0;
}
