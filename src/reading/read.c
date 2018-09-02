/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/02 19:59:34 by dlaurent         ###   ########.fr       */
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
}

static void	sh_read_esc(t_shell *shell, unsigned char c)
{
	int	i;

	i = -1;
	(void)shell;
	if (c == 65)// up arrow
		return ;
	else if (c == 66)// down arrow
		return ;
	else if (c == 67
	&& shell->read->cursor_abs_pos < shell->read->buffer_len
	&& shell->read->cursor_rel_pos < shell->read->w_width)
	{
		ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
		shell->read->cursor_abs_pos++;
		shell->read->cursor_rel_pos++;
	}
	else if (c == 67
	&& shell->read->cursor_rel_pos < shell->read->cursor_abs_pos)
	{
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
		shell->read->cursor_abs_pos++;
		shell->read->cursor_rel_pos = 0;
	}
	else if (c == 68
	&& shell->read->cursor_abs_pos > 0
	&& shell->read->cursor_rel_pos != 0)
	{
		ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		shell->read->cursor_abs_pos--;
		shell->read->cursor_rel_pos--;
	}
	else if (c == 68
	&& shell->read->cursor_rel_pos == 0
	&& shell->read->cursor_abs_pos > 0)
	{
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		while (++i < shell->read->w_width)
			ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		shell->read->cursor_abs_pos--;
		shell->read->cursor_rel_pos = shell->read->w_width;		
	}
	else if (c == 70) // fn+right arrow
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0)); // To be found
	else if (c == 72)// fn+left arrow
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
}

static void	sh_read_del(t_shell *shell)
{
	(void)shell;
	ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
	ft_putstr(tgetstr("dc", NULL));
}

static void	sh_parse_buffer(t_shell *shell, unsigned char *buffer)
{
	unsigned char	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == 10)
			cmd_run(shell);
		else
		{
			shell->read->buffer[shell->read->buffer_len] = buffer[i];
			shell->read->buffer_len++;
			shell->read->cursor_abs_pos++;
			shell->read->cursor_rel_pos =
			(shell->read->cursor_rel_pos == shell->read->w_width)
			? 0 : shell->read->cursor_rel_pos + 1;
			ft_putchar(buffer[i]);
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
	unsigned char	buffer[3];

	bzero(buffer, 4);
	while (TRUE)
	{
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
