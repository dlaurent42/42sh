/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_beginning_of_line.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 10:35:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 15:18:40 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_move_beginning_of_line(t_shell *shell)
{
	sh_debug(shell, "before move bol");
	if (shell->term->cursor.y == 0)
		while (shell->term->cursor.x > shell->term->header.display_length_mod)
			sh_move_left(shell);
	else
	{
		ft_putstr("\x1b\x5b\x48");
		sh_set_rel_pos(shell, shell->term->cursor.x, -1);
		shell->term->cursor.abs_pos -= shell->term->cursor.x;
		shell->term->cursor.x = 0;
	}
	sh_debug(shell, "after move bol");
}
