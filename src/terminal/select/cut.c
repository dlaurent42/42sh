/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:43:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 15:51:12 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_cut_delete(t_shell *sh, int start, int len)
{
	while (sh->buffer.content[start + len])
	{
		sh->buffer.content[start] = sh->buffer.content[start + len];
		start++;
	}
	while (sh->buffer.content[start])
	{
		sh->buffer.content[start] = '\0';
		start++;
	}
	sh->buffer.display_len = ft_strlenu(sh->buffer.content);
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content);
}

static void	sh_move_cursor(t_shell *sh, int x, int y)
{
	sh->cursor.y = (sh->buffer.display_len + sh->prompt.len_mod)
		/ sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->buffer.display_len + sh->prompt.len_mod) % sh->window.width
		: sh->buffer.display_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.rel_pos = sh->buffer.unicode_len;
	sh_move_to_xy(sh, x, y);
}

void		sh_cut_selection(t_shell *sh)
{
	int	x;
	int	y;
	int	len;
	int	start;

	x = sh->cursor.x;
	y = sh->cursor.y;
	sh_debug(sh, "before", NULL);
	if (!sh->modes.select)
		return ;
	sh->modes.browse = FALSE;
	len = sh_get_selection_len(sh);
	start = sh->selection.start_rel;
	sh_copy_selection(sh);
	sh_cut_delete(sh, start, len);
	sh_move_home(sh);
	ft_putstr(K_DEL_ALL);
	ft_putstr(sh->buffer.content);
	sh_move_cursor(sh, x, y);
	sh_debug(sh, "after", NULL);
}
