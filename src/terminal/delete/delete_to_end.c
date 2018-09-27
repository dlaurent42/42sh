/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_to_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:34:51 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 15:24:59 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void					sh_delete_to_end(t_shell *sh)
{
	int	curr_pos;

	curr_pos = sh->cursor.abs_pos;
	sh_move_end(sh);
	while (sh->cursor.abs_pos != curr_pos)
		sh_delete_char(sh);
}
