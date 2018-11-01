/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:47:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 13:22:39 by dlaurent         ###   ########.fr       */
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
	buffer_len = sh->buffer.display_len + 1;
	prompt_len = sh->prompt.len_mod;
	window_width = sh->window.width;
	sh->cursor.y = (buffer_len + prompt_len) / window_width;
	sh->cursor.x = (sh->cursor.y)
		? (buffer_len + prompt_len) % window_width
		: buffer_len;
	if ((y == 0 && x + 2 + prompt_len > window_width)
	|| (y > 0 && x + 2 > window_width))
		sh_move_to_xy(sh, 0, y + 1);
	else
		sh_move_to_xy(sh, x + 1, y);
}

static int	sh_add_char(t_shell *sh, char c)
{
	int	i;

	i = sh->buffer.unicode_len;
	if (sh->buffer.ushift + sh->buffer.unicode_len + 1 >= ARG_MAX)
		return (-1);
	while (i > sh->cursor.rel_pos)
	{
		sh->buffer.content[sh->buffer.ushift + i] =
		sh->buffer.content[sh->buffer.ushift + i - 1];
		i--;
	}
	sh->buffer.content[sh->buffer.ushift + i] = c;
	sh->buffer.display_len++;
	sh->buffer.unicode_len++;
	return (sh->cursor.rel_pos);
}

static int	sh_add_wchar(t_shell *sh, unsigned char c)
{
	int			i;
	static char	pointer = 0;
	static char	counter = 0;

	if (sh->buffer.ushift + sh->buffer.unicode_len + 1 >= ARG_MAX)
		return (-1);
	i = sh->buffer.unicode_len;
	while (i > sh->cursor.rel_pos)
	{
		sh->buffer.content[sh->buffer.ushift + i] =
		sh->buffer.content[sh->buffer.ushift + i - 1];
		i--;
	}
	sh->buffer.content[sh->buffer.ushift + i] = c;
	sh->buffer.display_len += (c >= 0b11000000) ? 1 : 0;
	sh->buffer.unicode_len++;
	sh->cursor.rel_pos++;
	pointer = (c >= 0b11000000) ? 1 : pointer;
	pointer = (c >= 0b11100000) ? 2 : pointer;
	pointer = (c >= 0b11110000) ? 3 : pointer;
	counter = (c < 0b11000000) ? counter - 1 : pointer;
	if (counter == 0)
		return (sh->cursor.rel_pos - pointer - 1);
	return (-1);
}

void		sh_fill_buffer(t_shell *sh)
{
	int				res;
	unsigned char	i;
	unsigned char	c;

	i = 0;
	while (sh->read->line[i])
	{
		res = -1;
		c = sh->read->line[i];
		if (c == 10)
			(!auto_completion(sh)) ? sh_command_prepare(sh) : 0;
		else
		{
			if ((unsigned char)c < 0b10000000 && ft_isprint(c))
				res = sh_add_char(sh, c);
			else if ((unsigned char)c >= 0b10000000)
				res = sh_add_wchar(sh, (unsigned char)c);
			(res != -1) ? ft_printf("%s ",
				sh->buffer.content + sh->buffer.ushift + res) : 0;
			(res != -1) ? sh_move_cursor(sh) : 0;
		}
		i++;
	}
}

void		sh_print_str(t_shell *sh, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_bzero(sh->read->line, LINE_SIZE);
		sh->read->line[0] = str[i];
		sh_fill_buffer(sh);
		i++;
	}
	ft_bzero(sh->read->line, LINE_SIZE);
}
