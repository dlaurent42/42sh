/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:47:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 03:48:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_select_set_pos(t_shell *sh)
{
	int	x;
	int	y;

	x = sh->cursor.x;
	y = sh->cursor.y;
	sh->cursor.rel_pos = sh->buffer.unicode_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.y = (sh->cursor.abs_pos + sh->prompt.len_mod) / sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->cursor.abs_pos + sh->prompt.len_mod) % sh->window.width
		: sh->cursor.abs_pos;
	sh_move_to_xy(sh, x, y);
}

void	sh_select_print(t_shell *sh)
{
	int	i;

	i = 0;
	while (sh->buffer.content[sh->cursor.rel_pos + i])
	{
		if (sh->cursor.rel_pos + i >= sh->selection.start_rel
		&& sh->cursor.rel_pos + i < sh->selection.stop)
			ft_printf("\e[7;37;40m%c\033[0m",
				sh->buffer.content[sh->cursor.rel_pos + i]);
		else
		{
			ft_printf("%s ", sh->buffer.content + sh->cursor.rel_pos + i);
			break ;
		}
		i++;
	}
}
