/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_from_home.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:34:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 19:06:46 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_move_cursor(t_shell *sh)
{
	sh->cursor.y = (sh->buffer.display_len + sh->prompt.len_mod)
		/ sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->buffer.display_len + sh->prompt.len_mod) % sh->window.width
		: sh->buffer.display_len;
	sh_move_to_xy(sh, 0, 0);
}

void		sh_delete_from_home(t_shell *sh)
{
	int	i;
	int	j;

	i = sh->buffer.ushift;
	j = sh->cursor.rel_pos;
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
	sh->buffer.display_len = ft_strlenu(sh->buffer.content + sh->buffer.ushift);
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content + sh->buffer.ushift);
	sh_move_home(sh);
	ft_putstr(K_DEL_ALL);
	ft_putstr(sh->buffer.content + sh->buffer.ushift);
	sh_move_cursor(sh);
}
