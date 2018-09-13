/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_up.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 20:21:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 15:37:17 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_move_up(t_shell *shell)
{
	sh_debug(shell, "before move up");
	if (shell->term->cursor.y == 0)
		return ;
	else if (shell->term->cursor.y == 1 && shell->term->cursor.x < shell->term->header.display_length_mod)
		while (shell->term->cursor.x < shell->term->header.display_length_mod)
			sh_move_right(shell);
	ft_putstr("\x1b\x5b\x41");
	sh_set_rel_pos(shell, shell->term->w_width, -1);
	shell->term->cursor.y--;
	shell->term->cursor.abs_pos -= shell->term->w_width;
	sh_debug(shell, "after move up");
}
