/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_to_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 16:53:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 12:12:06 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_select_home_reset_params(t_shell *sh, int len, int ulen)
{
	sh->buffer.display_len -= len;
	sh->buffer.unicode_len -= ulen;
	sh->cursor.y = (sh->prompt.len_mod + sh->buffer.display_len)
		/ sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->prompt.len_mod + sh->buffer.display_len) % sh->window.width
		: sh->buffer.display_len;
	sh_move_to_xy(sh, 0, 0);
}

void		sh_select_home(t_shell *sh)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = sh->cursor.rel_pos;
	k = sh->cursor.abs_pos;
	if (sh->cursor.abs_pos == 0)
		return ;
	sh_move_home(sh);
	ft_putstr(CLEAR_TO_EOL);
	while (sh->buffer.content[i + j])
	{
		sh->buffer.content[i] = sh->buffer.content[i + j];
		i++;
	}
	while (sh->buffer.content[i])
	{
		sh->buffer.content[i] = '\0';
		i++;
	}
	ft_putstr(sh->buffer.content);
	sh_select_home_reset_params(sh, k, j);
}
