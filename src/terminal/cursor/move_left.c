/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 15:20:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_move_left(t_shell *shell)
{
	int	i;

	i = 0;
	sh_debug(shell, "before move left");
	if (shell->term->cursor.abs_pos == 0)
		return ;
	if (shell->term->cursor.x > 0)
	{
		ft_putstr("\x1b\x5b\x44");
		shell->term->cursor.x--;
		shell->term->cursor.abs_pos--;
		sh_set_rel_pos(shell, 1, -1);
	}
	else
	{
		sh_move_up(shell);
		sh_move_end_of_line(shell);
	}
	sh_debug(shell, "after move left");
}
