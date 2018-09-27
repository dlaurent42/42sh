/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 13:28:44 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/25 16:04:14 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_move_down(t_shell *sh)
{
	if (sh->cursor.abs_pos + sh->window.width > sh->buffer.display_len)
		return (sh_move_end(sh));
	ft_putstr(K_DOWN);
	sh->cursor.abs_pos += sh->window.width;
	sh->cursor.y++;
	if (sh->cursor.y == 1)
		sh->cursor.x += sh->prompt.len_mod;
	sh_set_rel_pos(sh, sh->window.width, 1);
}
