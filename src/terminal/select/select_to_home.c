/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_to_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 16:53:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 13:00:25 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_select_home(t_shell *sh)
{
	if (sh->cursor.abs_pos == 0)
		return ;
	sh->selection.stop = (sh->selection.stop == sh->cursor.abs_pos)
		? sh->selection.start_abs
		: sh->cursor.abs_pos;
	sh->selection.start_abs = 0;
	sh->selection.start_rel = 0;
	sh_move_home(sh);
	sh_select_print(sh);
}
