/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/04 19:53:46 by dlaurent         ###   ########.fr       */
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
	ft_printf("%s", shell->read->buffer);
	ft_putendl("\n---Command sent---");
	shell->read->buffer_len = 0;
	shell->read->cursor_abs_pos = 0;
	shell->read->cursor_rel_pos = 0;
	shell->read->display_mode = FALSE;
	bzero(shell->read->buffer, ARG_MAX);
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
	if (shell->read->cursor_abs_pos == 0)
		return ;
	if (shell->read->cursor_rel_pos == 0)
	{
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		while (++i < shell->read->w_width)
			ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
		shell->read->cursor_rel_pos = shell->read->w_width;
	}
	else
	{
		ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		shell->read->cursor_rel_pos--;
	}
	ft_putstr(tgetstr("dc", NULL));
	shell->read->cursor_abs_pos--;
	shell->read->buffer_len--;
}

static void	sh_parse_buffer(t_shell *shell, unsigned char *buffer)
{
	unsigned char	i;

	i = 0;
	shell->read->display_mode = TRUE;
	while (buffer[i])
	{
		if (buffer[i] == 10)
			cmd_run(shell);
		else
		{
			shell->read->buffer[shell->read->cursor_abs_pos] = buffer[i];
			shell->read->buffer_len++;
			shell->read->cursor_abs_pos++;
			shell->read->cursor_rel_pos =
			(shell->read->cursor_rel_pos == shell->read->w_width)
			? 0 : shell->read->cursor_rel_pos + 1;
			ft_printf("%s%c%s", tgetstr("im", NULL), buffer[i], tgetstr("ei", NULL));
		}
		i++;
	}
}

static void	sh_read_autocompletion(t_shell *shell)
{
	shell->read->auto_completion_mode = TRUE;
}

void		sh_read(t_shell *shell)
{
	unsigned char	buffer[4];

	bzero(buffer, 4);
	while (TRUE)
	{
		if (!shell->read->buffer_len && !shell->read->display_mode
		&& (shell->read->display_mode = TRUE))
			ft_printf("%s ", shell->read->header);
		read(0, buffer, 3);
		if (buffer[0] == 4)
			break ;
		else if (buffer[0] == 27 && buffer[1] == 91)
			sh_read_esc(shell, buffer[2]);
		else if (buffer[0] == 127)
			sh_read_del(shell);
		else if (buffer[0] == 9)
			sh_read_autocompletion(shell);
		else
			sh_parse_buffer(shell, buffer);
		bzero(buffer, 4);
	}
}
