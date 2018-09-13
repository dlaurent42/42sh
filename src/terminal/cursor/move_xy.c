/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_xy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 11:18:46 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_move_to_xy(t_shell *shell, unsigned int x, unsigned int y)
{
	sh_debug(shell, "before move xy");
	while (shell->term->cursor.x != x && shell->term->cursor.y != y)
	{
		if (shell->term->cursor.y > y)
			sh_move_up(shell);
		else if (shell->term->cursor.y < y)
			sh_move_down(shell);
		if (x == 0)
			sh_move_beginning_of_line(shell);
		else if (x == shell->term->w_width - 1)
			sh_move_end_of_line(shell);
		else if (shell->term->cursor.x > x)
			sh_move_left(shell);
		else if (shell->term->cursor.x < x)
			sh_move_right(shell);
	}
	sh_debug(shell, "after move xy");
}
