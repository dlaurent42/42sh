/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 19:03:45 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/29 17:12:43 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_reset_cursor_after_resize(t_shell *sh, int x, int y)
{
	int	i;

	i = 0;
	while (++i < sh->prompt.rows)
		ft_putstr(K_DOWN);
	i = 0;
	while (++i <= sh->prompt.len_mod)
		ft_putstr(K_RIGHT);
	while (sh->cursor.y < y)
	{
		ft_putstr(K_DOWN);
		sh->cursor.y++;
	}
	sh->cursor.x = (y) ? sh->prompt.len_mod : 0;
	while (sh->cursor.x != x)
	{
		sh->cursor.x > x
			? ft_putstr(K_LEFT)
			: ft_putstr(K_RIGHT);
		sh->cursor.x += (sh->cursor.x > x)
			? (-1)
			: 1;
	}
}

static void	sh_resize_history_mode(t_shell *sh)
{
	ft_putstr(sh->buffer.content + sh->buffer.ushift);
	ft_putchar(' ');
	ft_putstr(SEARCH_PROMPT);
	ft_putstr(sh->search.content);
	ft_putchar('_');
}

static void	sh_resize_normal_mode(t_shell *sh, int x, int y)
{
	ft_printf("%s %s", sh->buffer.content + sh->buffer.ushift, K_COL_ROW_0);
	sh_reset_cursor_after_resize(sh, x, y);
}

void		sh_window_resize(t_shell *sh)
{
	int			x;
	int			y;
	t_winsize	window;

	ioctl(0, TIOCGWINSZ, &window);
	sh->window.width = window.ws_col;
	sh->window.height = window.ws_row;
	sh->prompt.len_mod = sh->prompt.len % sh->window.width;
	sh->prompt.rows = sh->prompt.len / sh->window.width + 1;
	y = (sh->cursor.abs_pos + sh->prompt.len_mod) / sh->window.width;
	x = (y)
		? (sh->cursor.abs_pos + sh->prompt.len) % sh->window.width
		: sh->cursor.abs_pos;
	sh->cursor.x = 0;
	sh->cursor.y = 0;
	ft_putstr(CLEAR_SCREEN);
	sh_print_prompt(sh);
	if (sh->modes.search)
		sh_resize_history_mode(sh);
	else
	{
		sh_resize_normal_mode(sh, x, y);
		if (sh->modes.auto_completion && sh->ac)
			auto_display(sh, sh->ac->window_resize, false);
	}
}
