/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeze.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:33:12 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 16:48:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_reset_buffer(t_shell *sh)
{
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content + sh->buffer.ushift);
	sh->buffer.display_len = ft_strlenu(sh->buffer.content + sh->buffer.dshift);
	sh->buffer.cmd = NULL;
	ft_bzero(sh->buffer.stored, ARG_MAX);
}

static void	sh_reset_cursor(t_shell *sh)
{
	sh->cursor.rel_pos = sh->buffer.unicode_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.y = (sh->prompt.len_mod + sh->buffer.display_len)
		/ sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->prompt.len_mod + sh->buffer.display_len)
		% sh->window.width
		: sh->buffer.display_len;
}

void		sh_search_freeze(t_shell *sh)
{
	if (sh->modes.search == FALSE)
		return ;
	ft_bzero(sh->search.content, sh->search.len);
	sh->search.len = 0;
	sh->search.match = NULL;
	sh->modes.search = FALSE;
	sh_history_move_cursor(sh);
	ft_putstr(K_DEL_ALL);
	ft_putstr(sh->prompt.content);
	ft_putstr(sh->buffer.content + sh->buffer.ushift);
	sh_reset_buffer(sh);
	sh_reset_cursor(sh);
	ft_putstr(CURSOR_SHOW);
}
