/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:51:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 19:11:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_copy_selection_to_buffer(t_shell *sh)
{
	int	i;
	int	j;

	i = sh->buffer.ushift + sh->cursor.rel_pos;
	j = 0;
	while (sh->selection.content[j] && i + 1 < ARG_MAX)
	{
		sh->buffer.content[i] = sh->selection.content[j];
		i++;
		j++;
	}
}

static void	sh_copy_rest_to_buffer(t_shell *sh, char *rest)
{
	int	i;
	int	j;

	i = sh->buffer.ushift
		+ sh->cursor.rel_pos
		+ ft_strlens(sh->selection.content);
	j = 0;
	while (rest[j] && i + j + 1 < ARG_MAX)
	{
		sh->buffer.content[i + j] = rest[j];
		j++;
	}
	sh->buffer.display_len = ft_strlenu(sh->buffer.content + sh->buffer.ushift);
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content + sh->buffer.ushift);
	ft_strdel(&rest);
}

static void	sh_move_cursor(t_shell *sh, int delta)
{
	int	x;
	int	y;

	y = (sh->cursor.abs_pos + delta + sh->prompt.len_mod) / sh->window.width;
	x = (y)
		? (sh->cursor.abs_pos + delta + sh->prompt.len_mod) % sh->window.width
		: sh->cursor.abs_pos + delta;
	sh->cursor.y = (sh->buffer.display_len + sh->prompt.len_mod)
		/ sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->buffer.display_len + sh->prompt.len_mod) % sh->window.width
		: sh->buffer.display_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.rel_pos = sh->buffer.unicode_len;
	sh->buffer.display_len = ft_strlenu(sh->buffer.content + sh->buffer.ushift);
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content + sh->buffer.ushift);
	sh_move_to_xy(sh, x, y);
}

void		sh_paste_selection(t_shell *sh)
{
	int		delta;
	char	*rest;

	if (!sh->selection.content)
		return ;
	sh->modes.browse = FALSE;
	rest = ft_strdups(
		sh->buffer.content
		+ sh->buffer.ushift
		+ sh->cursor.rel_pos);
	sh_copy_selection_to_buffer(sh);
	(rest) ? sh_copy_rest_to_buffer(sh, rest) : 0;
	ft_putstr(CLEAR_TO_EOL);
	ft_putstr(sh->buffer.content + sh->buffer.ushift + sh->cursor.rel_pos);
	delta = (sh->buffer.unicode_len
		+ ft_strlens(sh->selection.content) >= ARG_MAX)
		? ARG_MAX - sh->buffer.unicode_len
		: ft_strlenu(sh->selection.content);
	sh_move_cursor(sh, delta);
}
