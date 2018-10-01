/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_up.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 16:03:02 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/25 16:06:14 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_select_up(t_shell *sh)
{
	int		cursor;

	cursor = sh->cursor.abs_pos - sh->window.width;
	if ((sh->cursor.y == 1 && sh->cursor.x < sh->prompt.len_mod)
	|| sh->cursor.y == 0)
		return (sh_select_home(sh));
	while (sh->cursor.abs_pos != cursor)
		sh_select_left_char(sh);
}
