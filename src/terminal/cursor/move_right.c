/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/14 14:52:41 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_move_right(t_shell *shell)
{
	if (shell->term->cursor.abs_pos >= shell->read->buffer.display_length)
		return ;
	if ((shell->term->cursor.y == 0 && shell->term->cursor.x + 2 + shell->term->header.display_length_mod > shell->term->window.width)
	|| (shell->term->cursor.y > 0 && shell->term->cursor.x + 2 > shell->term->window.width))
	{
		ft_putstr(K_DOWN);
		ft_putstr(K_COL_0);
		shell->term->cursor.x = 0;
		shell->term->cursor.y++;
	}
	else
	{
		ft_putstr(K_RIGHT);
		shell->term->cursor.x++;
	}
	shell->term->cursor.abs_pos++;
	sh_set_rel_pos(shell, 1, 1);
}
