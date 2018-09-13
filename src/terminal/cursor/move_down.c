/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_down.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 20:21:24 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 15:25:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_move_down(t_shell *shell)
{
	sh_debug(shell, "before move down");
	if (shell->term->cursor.y >= (shell->read->buffer.display_length + shell->term->header.display_length_mod + 1) / shell->term->w_width)
		return ;
	else if (shell->term->cursor.abs_pos + shell->term->w_width > shell->read->buffer.display_length)
		while (shell->term->cursor.abs_pos + shell->term->w_width > shell->read->buffer.display_length)
			sh_move_left(shell);
	ft_putstr("\x1b\x5b\x42");
	sh_set_rel_pos(shell, shell->term->w_width, 1);
	shell->term->cursor.y++;
	shell->term->cursor.abs_pos += shell->term->w_width;
	sh_debug(shell, "after move down");
}
