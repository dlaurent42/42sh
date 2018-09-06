/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/06 11:06:24 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_move_left(t_shell *shell)
{
	int	i;

	i = -1;
	if (shell->term->cursor.absolute_position > 0
	&& shell->term->cursor.relative_position != 0)
	{
		ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		shell->term->cursor.absolute_position--;
		shell->term->cursor.relative_position--;
	}
	else if (shell->term->cursor.relative_position == 0
	&& shell->term->cursor.absolute_position > 0)
	{
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		while (++i < shell->term->w_width)
			ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		shell->term->cursor.absolute_position--;
		shell->term->cursor.relative_position = shell->term->w_width;
	}
}

void	sh_move_right(t_shell *shell)
{
	if (shell->term->cursor.absolute_position < shell->read->buffer.length
	&& shell->term->cursor.relative_position < shell->term->w_width)
	{
		ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
		shell->term->cursor.absolute_position++;
		shell->term->cursor.relative_position++;
	}
	else if (shell->term->cursor.relative_position < shell->term->cursor.absolute_position)
	{
		ft_putstr(tgoto(tgetstr("do", NULL), 0, 0));
		ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
		shell->term->cursor.absolute_position++;
		shell->term->cursor.relative_position = 0;
	}
	else
	{
		ft_printf("\nrel:%d\nabs:%d\n", shell->term->cursor.relative_position, shell->term->cursor.absolute_position);
	}
}

void	sh_move_start(t_shell *shell)
{
	unsigned char	i;

	i = -1;
	while (shell->term->cursor.absolute_position > shell->term->w_width)
	{
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		shell->term->cursor.absolute_position -= shell->term->w_width;
	}
	ft_putstr(tgoto(tgetstr("ch", NULL), 0, 0));
	while (++i < shell->term->header.length + 1)
		ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
	shell->term->cursor.absolute_position = 0;
	shell->term->cursor.relative_position = 0;
}

void	sh_move_end(t_shell *shell)
{
	(void)shell;
}

