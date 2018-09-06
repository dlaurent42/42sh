/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:47:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/06 15:38:11 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_add_character(t_shell *shell, char c)
{
	unsigned char	i;

	i = shell->read->buffer.length;
	while (i > shell->term->cursor.abs_pos)
	{
		shell->read->buffer.content[i] = shell->read->buffer.content[i - 1];
		i--;
	}
	shell->read->buffer.content[i] = c;
	shell->read->buffer.length++;
}

static void	sh_move_cursor(t_shell *shell)
{
	sh_debug(shell, "before fill");
	if ((shell->term->cursor.y == 0 && shell->term->cursor.x + 2 + shell->term->header.length_mod >= shell->term->w_width)
	|| (shell->term->cursor.y > 0 && shell->term->cursor.x + 1 >= shell->term->w_width))
	{
		shell->term->cursor.x = 0;
		shell->term->cursor.y++;
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
	}
	else
		shell->term->cursor.x++;
	shell->term->cursor.abs_pos++;
	sh_debug(shell, "after fill");
}

void		sh_fill_buffer(t_shell *shell)
{
	unsigned char	i;

	i = 0;
	sh_debug(shell, shell->read->line);
	while (shell->read->line[i])
	{
		if (shell->read->line[i] == 10)
			sh_command_run(shell);
		else
		{
			sh_add_character(shell, shell->read->line[i]);
			sh_move_cursor(shell);
		}
		i++;
	}
	ft_printf("%s%s%s", tgetstr("im", NULL), shell->read->line, tgetstr("ei", NULL));
}
