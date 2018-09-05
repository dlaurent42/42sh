/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/05 20:37:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cb: empty current line from beginning to cursor
// nd: move 1 char to left
// le: move 1 char to right
// do: move 1 line down
// up: move 1 line up
// ch: move to col 0 of curr line

// co: number of columns
// li: numner of lines

// 67 : right
// 68 : left

static void	cmd_run(t_shell *shell)
{
	struct winsize w;

    ioctl(0, TIOCGWINSZ, &w);
	ft_printf("\nNumber of columns: %d\nNumber of lines: %d\n", w.ws_col, w.ws_row);
	ft_printf("%s", shell->read->buffer.content);
	ft_putendl("\n---Command sent---");
	shell->term->display_mode = FALSE;
	bzero(shell->read->buffer.content, ARG_MAX);
	shell->read->buffer.length = 0;
	shell->read->buffer.cmd = NULL;
}

static void	sh_read_esc(t_shell *shell, unsigned char c)
{
	if (c == 65)// up arrow
		return ;
	else if (c == 66)// down arrow
		return ;
	else if (c == 67 || c == 68 || c == 70 || c == 72)
		sh_move_cursor(shell, c);
}

static void	sh_read_del(t_shell *shell)
{
	int	i;

	i = -1;
	if (shell->term->cursor.absolute_position == 0)
		return ;
	if (shell->term->cursor.relative_position == 0)
	{
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		while (++i < shell->term->w_width)
			ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
		shell->term->cursor.relative_position = shell->term->w_width;
	}
	else
	{
		ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		shell->term->cursor.relative_position--;
	}
	ft_putstr(tgetstr("dc", NULL));
	shell->term->cursor.absolute_position--;
	shell->read->buffer.length--;
}

static void	sh_parse_buffer(t_shell *shell)
{
	unsigned char	i;

	i = 0;
	shell->term->display_mode = TRUE;
	while (shell->read->line[i])
	{
		if (shell->read->line[i] == 10)
			cmd_run(shell);
		else
		{
			shell->read->buffer.content[shell->term->cursor.absolute_position] = shell->read->line[i];
			shell->read->buffer.length++;
			shell->term->cursor.absolute_position++;
			shell->term->cursor.relative_position =
			(shell->term->cursor.relative_position == shell->term->w_width)
			? 0 : shell->term->cursor.relative_position + 1;
			ft_printf("%s%c%s", tgetstr("im", NULL), shell->read->line[i], tgetstr("ei", NULL));
		}
		i++;
	}
}

static void	sh_read_autocompletion(t_shell *shell)
{
	shell->term->auto_completion_mode = TRUE;
}

void		sh_read(t_shell *shell)
{
	while (TRUE)
	{
		if (!shell->read->buffer.length && !shell->term->display_mode
		&& (shell->term->display_mode = TRUE))
			ft_printf("%s ", shell->term->header.content);
		read(0, shell->read->line, 3);
		if (shell->read->line[0] == 4)
			break ;
		else if (shell->read->line[0] == 27 && shell->read->line[1] == 91)
			sh_read_esc(shell, shell->read->line[2]);
		else if (shell->read->line[0] == 127)
			sh_read_del(shell);
		else if (shell->read->line[0] == 9)
			sh_read_autocompletion(shell);
		else
			sh_parse_buffer(shell);
		bzero(shell->read->line, 4);
	}
}
