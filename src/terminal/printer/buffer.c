/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:47:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/20 14:41:58 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_move_cursor(t_shell *sh)
{
	int	x;
	int	y;
	int	buffer_len;
	int	prompt_len;
	int	window_width;

	x = sh->cursor.x;
	y = sh->cursor.y;
	buffer_len = sh->read->buffer.display_len + 1;
	prompt_len = sh->prompt.len_mod;
	window_width = sh->window.width;
	sh->cursor.y = (buffer_len + prompt_len) / window_width;
	sh->cursor.x = (sh->cursor.y)
		? (buffer_len + prompt_len) % window_width
		: buffer_len;
	if ((y == 0 && x + 2 + prompt_len > window_width) || (y > 0 && x + 2 > window_width))
		sh_move_to_xy(sh, 0, y + 1);
	else
		sh_move_to_xy(sh, x + 1, y);
}

static void	sh_add_char(t_shell *sh, char c)
{
	int	i;

	i = sh->read->buffer.unicode_len;
	while (i > sh->cursor.rel_pos)
	{
		sh->read->buffer.content[i] = sh->read->buffer.content[i - 1];
		i--;
	}
	sh->read->buffer.content[i] = c;
	sh->read->buffer.display_len++;
	sh->read->buffer.unicode_len++;
	ft_printf("%s ",
		sh->read->buffer.content
		+ sh->cursor.rel_pos);
	sh_move_cursor(sh);
}

static void	sh_add_wchar(t_shell *sh, unsigned char c)
{
	int			i;
	static char	pointer = 0;
	static char	counter = 0;

	i = sh->read->buffer.unicode_len;
	while (i > sh->cursor.rel_pos)
	{
		sh->read->buffer.content[i] = sh->read->buffer.content[i - 1];
		i--;
	}
	sh->read->buffer.content[i] = c;
	sh->read->buffer.display_len += (c >= 0b11000000) ? 1 : 0;
	sh->read->buffer.unicode_len++;
	sh->cursor.rel_pos++;
	pointer = (c >= 0b11000000) ? 1 : pointer;
	pointer = (c >= 0b11100000) ? 2 : pointer;
	pointer = (c >= 0b11110000) ? 3 : pointer;
	counter = (c < 0b11000000) ? counter - 1 : pointer;
	if (counter == 0)
	{
		ft_printf("%s ",
			sh->read->buffer.content
			+ sh->cursor.rel_pos - pointer - 1);
		sh_move_cursor(sh);
	}
}

void		sh_fill_buffer(t_shell *sh)
{
	unsigned char	i;

	i = 0;
	while (sh->read->line[i])
	{
		if (sh->read->line[i] == 10)
			sh_command_run(sh);
		else if ((unsigned char)sh->read->line[i] < 0b10000000 && ft_isprint(sh->read->line[i]))
			sh_add_char(sh, sh->read->line[i]);
		else if ((unsigned char)sh->read->line[i] >= 0b10000000)
			sh_add_wchar(sh, (unsigned char)sh->read->line[i]);
		i++;
	}
}
