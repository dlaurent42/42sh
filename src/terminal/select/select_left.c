/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 01:47:24 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 05:05:56 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_select_left_char(t_shell *sh)
{
	int	i;

	i = 0;
	if (sh->cursor.abs_pos == 0)
		return ;
	if (sh->modes.select == TRUE
	&& sh->cursor.abs_pos - 1 >= sh->selection.start_rel)
	{
		sh_move_left(sh);
		return ;
	}
	(!sh->modes.select) ? sh->selection.stop = sh->cursor.rel_pos : 0;
	sh->modes.select = TRUE;
	sh_move_left(sh);
	sh->selection.start_rel = sh->cursor.rel_pos;
	sh->selection.start_abs = sh->cursor.abs_pos;
	ft_putstr(K_DEL);
	ft_putstr(K_LEFT);
	sh_select_print(sh);
	sh_select_set_pos(sh);
}
