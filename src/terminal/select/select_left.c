/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 01:47:24 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 21:53:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		sh_select_char(t_shell *sh)
{
	(!sh->modes.select) ? sh->selection.stop = sh->cursor.abs_pos : 0;
	sh->modes.select = TRUE;
	sh_move_left(sh);
	sh->selection.start_rel = sh->cursor.rel_pos;
	sh->selection.start_abs = sh->cursor.abs_pos;
	ft_putstr(K_DEL);
	ft_putstr(K_LEFT);
	sh_select_print(sh);
}

static void		sh_unselect_char(t_shell *sh)
{
	sh_move_left(sh);
	sh->selection.stop = sh->cursor.abs_pos;
	sh_select_print(sh);
}

void			sh_select_left_char(t_shell *sh)
{
	if (sh->cursor.abs_pos == 0)
		return ;
	if (sh->modes.select && sh->selection.stop == sh->selection.start_abs)
		return (sh_unselect(sh));
	(sh->modes.select && sh->cursor.abs_pos == sh->selection.stop)
		? sh_unselect_char(sh)
		: sh_select_char(sh);
}
