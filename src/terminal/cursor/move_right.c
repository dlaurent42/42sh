/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 15:20:11 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_move_right(t_shell *shell)
{
	sh_debug(shell, "before move right");
	if (shell->term->cursor.abs_pos >= shell->read->buffer.display_length)
		return ;
	if ((shell->term->cursor.y == 0 && shell->term->cursor.x + 1 + shell->term->header.display_length_mod + 1 >= shell->term->w_width)
	|| (shell->term->cursor.y > 0 && shell->term->cursor.x + 1 >= shell->term->w_width))
	{
		sh_move_down(shell);
		sh_move_beginning_of_line(shell);
	}
	else
	{
		ft_putstr("\x1b\x5b\x43");
		shell->term->cursor.x++;
		shell->term->cursor.abs_pos++;
		sh_set_rel_pos(shell, 1, 1);
	}
	sh_debug(shell, "after move right");
}
