/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:51:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 16:16:55 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_copy_selection_to_buffer(t_shell *sh)
{
	int	i;
	int	j;

	i = sh->cursor.rel_pos;
	j = 0;
	while (sh->selection.content[j])
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

	i = sh->cursor.rel_pos + ft_strlens(sh->selection.content);
	j = 0;
	while (rest[j])
	{
		sh->buffer.content[i + j] = rest[j];
		j++;
	}
	sh->buffer.display_len = ft_strlenu(sh->buffer.content);
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content);
	ft_strdel(&rest);
}

static void	sh_move_cursor(t_shell *sh)
{
	int	x;
	int	y;

	x = sh->cursor.x;
	y = sh->cursor.y;
	sh->cursor.y = (sh->buffer.display_len + sh->prompt.len_mod)
		/ sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->buffer.display_len + sh->prompt.len_mod) % sh->window.width
		: sh->buffer.display_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.rel_pos = sh->buffer.unicode_len;
	sh->buffer.display_len = ft_strlenu(sh->buffer.content);
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content);
	sh_move_to_xy(sh, x, y);
}

void		sh_paste_selection(t_shell *sh)
{
	char	*rest;

sh_debug(sh, "01", NULL);
	if (!sh->selection.content)
		return ;
	sh->modes.browse = FALSE;
sh_debug(NULL, "02", NULL);
	rest = ft_strdups(sh->buffer.content + sh->cursor.rel_pos);
sh_debug(NULL, rest, NULL);
sh_debug(NULL, "03", NULL);
	sh_copy_selection_to_buffer(sh);
sh_debug(NULL, "04", NULL);
	(rest) ? sh_copy_rest_to_buffer(sh, rest) : 0;
sh_debug(NULL, "06", NULL);
	ft_putstr(CLEAR_TO_EOL);
sh_debug(NULL, "07", NULL);
	ft_putstr(sh->buffer.content + sh->cursor.rel_pos);
sh_debug(NULL, "08", NULL);
	sh_move_cursor(sh);
sh_debug(sh, "09", NULL);
}
