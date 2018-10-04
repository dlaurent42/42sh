/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 16:03:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 13:49:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_select_up(t_shell *sh)
{
	char		add;

	if (sh->cursor.abs_pos == 0)
		return ;
	if (!sh->modes.select)
		sh->selection.stop = sh->cursor.abs_pos;
	add = (sh->modes.select && sh->cursor.abs_pos == sh->selection.start_abs)
		? TRUE : FALSE;
	sh_move_up(sh);
	if (!sh->modes.select)
	{
		sh->selection.start_abs = sh->cursor.abs_pos;
		sh->selection.start_rel = sh->cursor.rel_pos;
		return (sh_select_print(sh));
	}
	if (sh->cursor.abs_pos < sh->selection.start_abs)
	{
		(add == FALSE) ? sh->selection.stop = sh->selection.start_abs : 0;
		sh->selection.start_abs = sh->cursor.abs_pos;
		sh->selection.start_rel = sh->cursor.rel_pos;
	}
	else
		sh->selection.stop = sh->cursor.abs_pos;
	sh_select_print(sh);
}
