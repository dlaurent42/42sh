/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:47:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/07 16:53:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_add_character(t_shell *shell, unsigned char c)
{
	unsigned int	i;

	if (c == 10)
		return (sh_command_run(shell));
	i = shell->read->buffer.unicode_length;
	while (i > shell->term->cursor.rel_pos)
	{
		shell->read->buffer.content[i] = shell->read->buffer.content[i - 1];
		i--;
	}
	shell->read->buffer.content[i] = c;
	if (c < 0b10000000 || c >= 0b11000000)
		shell->read->buffer.display_length++;
	shell->read->buffer.unicode_length++;
}

static void	sh_move_cursor(t_shell *shell, unsigned char c) // = move right ?
{
	unsigned int	target_x;
	unsigned int	target_y;
	if (c >= 0b10000000 && c < 0b11000000)
	{
		shell->term->cursor.rel_pos++;
		return ;
	}
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
	shell->term->cursor.x = ;
	shell->term->cursor.y = (shell->read->buffer.display_length + shell->term->header.display_length_mod + 1) % shell->term->w_width;
	shell->term->cursor.rel_pos = shell->read->buffer.unicode_length;
	shell->term->cursor.abs_pos = shell->read->buffer.display_length;
	while (shell->term->cursor.x != target_x && shell->term->cursor.y != target_y)
		sh_move_left(shell);
}

int			myputchr(int c)
{
	write(1, &c, 1);
	return (c);
}

void		sh_fill_buffer(t_shell *shell)
{
	unsigned char	i;
	unsigned char	move;

	i = 0;
	move = 0;
	while (shell->read->line[i])
	{
		sh_add_character(shell, shell->read->line[i]);
		if (shell->read->line[i] != 10)
		{
			sh_move_cursor(shell, shell->read->line[i]);
			//ft_printf("%s", shell->read->buffer.content + shell->term->cursor.rel_pos - 1);
			tputs((char *)(shell->read->buffer.content + shell->term->cursor.rel_pos - 1), 0, myputchr);
		}
		i++;
	}
	sh_debug(shell, "after fill");
}
