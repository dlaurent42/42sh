/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_xy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/14 01:00:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_move_y(t_shell *shell, unsigned int y)
{
	while (shell->term->cursor.y < y)
	{
		ft_putstr(K_DOWN);
		shell->term->cursor.y++;
		shell->term->cursor.x = shell->term->header.display_length_mod;
		shell->term->cursor.abs_pos += shell->term->w_width;
	}
}

static void	sh_move_x(t_shell *shell, unsigned int x)
{
	while (shell->term->cursor.x != x)
	{
		shell->term->cursor.x > x
			? ft_putstr(K_LEFT)
			: ft_putstr(K_RIGHT);
		shell->term->cursor.abs_pos += (shell->term->cursor.x > x)
			? (-1)
			: 1;
		shell->term->cursor.x += (shell->term->cursor.x > x)
			? (-1)
			: 1;
	}
}

void		sh_move_to_xy(t_shell *shell, unsigned int x, unsigned int y)
{
	shell->term->cursor.y -= (shell->term->cursor.x == 0) ? 1 : 0;
	sh_move_home(shell);
	sh_move_y(shell, y);
	sh_move_x(shell, x);
	sh_set_rel_pos(shell, shell->term->cursor.abs_pos, 1);
}
