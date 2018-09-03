/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/03 19:16:34 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_move_left(t_shell *shell)
{
	int	i;

	i = -1;
	if (shell->read->cursor_abs_pos > 0
	&& shell->read->cursor_rel_pos != 0)
	{
		ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		shell->read->cursor_abs_pos--;
		shell->read->cursor_rel_pos--;
	}
	else if (shell->read->cursor_rel_pos == 0
	&& shell->read->cursor_abs_pos > 0)
	{
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		while (++i < shell->read->w_width)
			ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		shell->read->cursor_abs_pos--;
		shell->read->cursor_rel_pos = shell->read->w_width;		
	}
}

static void	sh_move_right(t_shell *shell)
{
	if (shell->read->cursor_abs_pos < shell->read->buffer_len
	&& shell->read->cursor_rel_pos < shell->read->w_width)
	{
		ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
		shell->read->cursor_abs_pos++;
		shell->read->cursor_rel_pos++;
	}
	else if (shell->read->cursor_rel_pos < shell->read->cursor_abs_pos)
	{
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
		shell->read->cursor_abs_pos++;
		shell->read->cursor_rel_pos = 0;		
	}
}

static void	sh_move_start(t_shell *shell)
{
	while (shell->read->cursor_abs_pos > shell->read->w_width)
	{
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		shell->read->cursor_abs_pos -= shell->read->w_width;
	}
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
	ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
	ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
	ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
	ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
	shell->read->cursor_abs_pos = 0;
	shell->read->cursor_rel_pos = 0;
}

static void sh_move_end(t_shell *shell)
{
	(void)shell;
}

void		sh_move_cursor(t_shell *shell, char c)
{
	if (c == 67)
		sh_move_right(shell);
	else if (c == 68)
		sh_move_left(shell);
	else if (c == 70)
		sh_move_end(shell);
	else if (c == 72)
		sh_move_start(shell);
}
