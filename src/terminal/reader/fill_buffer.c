/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:47:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/10 22:59:29 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_move_cursor(t_shell *shell)
{
	unsigned int	target_x;
	unsigned int	target_y;

	if ((shell->term->cursor.y == 0 && shell->term->cursor.x + 2 + shell->term->header.display_length_mod >= shell->term->w_width)
	|| (shell->term->cursor.y > 0 && shell->term->cursor.x + 1 >= shell->term->w_width))
	{
		target_x = 0;
		target_y = shell->term->cursor.y + 1;
	}
	else
	{
		target_x = shell->term->cursor.x + 1;
		target_y = shell->term->cursor.y;
	}
	shell->term->cursor.y = (shell->read->buffer.display_length + shell->term->header.display_length_mod + 1) / shell->term->w_width;
	shell->term->cursor.x = (shell->term->cursor.y == 0) ? shell->read->buffer.display_length
	: (shell->read->buffer.display_length + shell->term->header.display_length_mod + 1) % shell->term->w_width;
	shell->term->cursor.rel_pos = shell->read->buffer.unicode_length;
	shell->term->cursor.abs_pos = shell->read->buffer.display_length;
	while (target_x != shell->term->cursor.x || target_y != shell->term->cursor.y)
		sh_move_left(shell);
}

static void	sh_add_char(t_shell *shell, unsigned char c)
{
	unsigned int	i;

	i = shell->read->buffer.unicode_length;
	while (i > shell->term->cursor.rel_pos)
	{
		shell->read->buffer.content[i] = shell->read->buffer.content[i - 1];
		i--;
	}
	shell->read->buffer.content[i] = c;
	shell->read->buffer.display_length++;
	shell->read->buffer.unicode_length++;
	ft_printf("%s", shell->read->buffer.content + shell->term->cursor.rel_pos);
	sh_move_cursor(shell);
}

static void	sh_add_wchar(t_shell *shell, unsigned char c)
{
	unsigned int			i;
	static unsigned char	pointer = 0;
	static unsigned char	counter = 0;

	i = shell->read->buffer.unicode_length;
	while (i > shell->term->cursor.rel_pos)
	{
		shell->read->buffer.content[i] = shell->read->buffer.content[i - 1];
		i--;
	}
	shell->read->buffer.content[i] = c;
	if (c >= 0b11000000)
		shell->read->buffer.display_length++;
	shell->read->buffer.unicode_length++;
	shell->term->cursor.rel_pos++;
	pointer = (c >= 0b11000000) ? 1 : pointer;
	pointer = (c >= 0b11100000) ? 2 : pointer;
	pointer = (c >= 0b11110000) ? 3 : pointer;
	counter = (c < 0b11000000) ? counter - 1 : pointer;
	if (counter == 0)
	{
		ft_printf("%s", shell->read->buffer.content + shell->term->cursor.rel_pos - pointer - 1);
		sh_move_cursor(shell);
	}
}

void		sh_fill_buffer(t_shell *shell)
{
	unsigned char	i;

	i = 0;
	while (shell->read->line[i])
	{
		if (shell->read->line[i] == 10)
			sh_command_run(shell);
		else if (shell->read->line[i] < 0b10000000)
			sh_add_char(shell, shell->read->line[i]);
		else
			sh_add_wchar(shell, shell->read->line[i]);
		i++;
	}
	sh_debug(shell, "after fill");
}
