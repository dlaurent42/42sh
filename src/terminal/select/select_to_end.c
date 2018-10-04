/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_to_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 16:55:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 16:55:12 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_select_end(t_shell *sh)
{
	int		i;

	i = 0;
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	if (!sh->modes.select)
	{
		sh->selection.start_abs = sh->cursor.abs_pos;
		sh->selection.start_rel = sh->cursor.rel_pos;
		sh->selection.stop = sh->buffer.display_len;
	}
	else if (sh->selection.stop == sh->cursor.abs_pos)
		sh->selection.stop = sh->buffer.display_len;
	else
	{
		sh->selection.start_abs = sh->selection.stop;
		sh->selection.start_rel = sh_get_start_rel_from_abs(sh);
		sh->selection.stop = sh->buffer.display_len;
	}
	sh_move_end(sh);
	sh_select_print(sh);
}
