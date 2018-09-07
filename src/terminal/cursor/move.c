/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/07 16:34:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_set_relative_position(t_shell *shell, char direction)
{
	unsigned char	c;

	shell->term->cursor.rel_pos += direction;
	c = shell->read->buffer.content[shell->term->cursor.rel_pos];
	while (c >= 0b10000000 && c < 0b11000000)
	{
		shell->term->cursor.rel_pos = shell->term->cursor.rel_pos + direction;
		c = shell->read->buffer.content[shell->term->cursor.rel_pos];
	}
}

void		sh_move_left(t_shell *shell)
{
	int	i;

	i = 0;
	sh_debug(shell, "before move left");
	if (shell->term->cursor.abs_pos == 0)
		return ;
	else if (shell->term->cursor.x > 0)
	{
		ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		shell->term->cursor.x--;
	}
	else
	{
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		while (i <= shell->term->w_width)
		{
			ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
			i++;
		}
		shell->term->cursor.y--;
		shell->term->cursor.x = (shell->term->cursor.y == 0)
		? shell->term->w_width - 1 - shell->term->header.display_length_mod - 1
		: shell->term->w_width - 1;
	}
	shell->term->cursor.abs_pos--;
	sh_set_relative_position(shell, -1);
	sh_debug(shell, "after move left");
}

void		sh_move_start(t_shell *shell)
{
	unsigned char	i;

	i = 0;
	sh_debug(shell, "before move start");
	if (shell->term->cursor.abs_pos == 0)
		return ;
	while (shell->term->cursor.y)
	{
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		shell->term->cursor.y--;
	}
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
	while (i < shell->term->header.display_length_mod + 1)
	{
		ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
		i++;
	}
	shell->term->cursor.x = 0;
	shell->term->cursor.y = 0;
	shell->term->cursor.abs_pos = 0;
	shell->term->cursor.rel_pos = 0;
	sh_debug(shell, "after move start");
}

void		sh_move_right(t_shell *shell) // just put else ?
{
	sh_debug(shell, "before move right");
	if (shell->term->cursor.abs_pos >= shell->read->buffer.display_length)
		return ;
	else if ((shell->term->cursor.y == 0 && shell->term->cursor.x + 1 + shell->term->header.display_length_mod + 1 >= shell->term->w_width)
	|| (shell->term->cursor.y > 0 && shell->term->cursor.x + 1 >= shell->term->w_width))
	{
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
		shell->term->cursor.abs_pos++;
		shell->term->cursor.x = 0;
		shell->term->cursor.y++;
	}
	else if ((shell->term->cursor.y == 0 && shell->term->cursor.x + 1 + shell->term->header.display_length_mod + 1 < shell->term->w_width)
	|| (shell->term->cursor.y > 0 && shell->term->cursor.x + 1 < shell->term->w_width))
	{
		ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
		shell->term->cursor.abs_pos++;
		shell->term->cursor.x++;
	}
	sh_set_relative_position(shell, 1);
	sh_debug(shell, "after move right");
}

void		sh_move_end(t_shell *shell)
{
	unsigned int	moves;

	moves = 0;
	sh_debug(shell, "before move end");
	if (shell->term->cursor.abs_pos >= shell->read->buffer.display_length)
		return ;
	while (moves * shell->term->w_width <= shell->read->buffer.display_length + shell->term->header.display_length_mod + 1)
		moves++;
	while (shell->term->cursor.y + 1 < moves)
	{
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
		shell->term->cursor.y++;
	}
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
	moves = (shell->term->header.display_length_mod + 1 + shell->read->buffer.display_length) % shell->term->w_width;
	shell->term->cursor.x = 0;
	while (moves--)
	{
		ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
		shell->term->cursor.x++;
	}
	shell->term->cursor.x -= (shell->term->cursor.y) ? 0 : (shell->term->header.display_length_mod + 1);
	shell->term->cursor.abs_pos = shell->read->buffer.display_length;
	shell->term->cursor.rel_pos = shell->read->buffer.unicode_length;
	sh_debug(shell, "after move end");
}
