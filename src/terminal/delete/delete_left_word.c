/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_left_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:35:28 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/29 01:37:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_delete_previous_word(t_shell *sh)
{
	int		del;

	del = sh->cursor.abs_pos;
	if (sh->cursor.abs_pos == 0)
		return ;
	sh_move_previous_word(sh);
	del -= sh->cursor.abs_pos;
	while (del >= 0)
	{
		sh_delete_current_char(sh);
		del--;
	}
}
