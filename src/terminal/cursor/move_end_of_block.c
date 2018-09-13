/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_end_of_block.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 15:28:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_move_end(t_shell *shell)
{
	sh_debug(shell, "before move end");
	while (shell->term->cursor.y < (shell->read->buffer.display_length + shell->term->header.display_length_mod + 1) / shell->term->w_width)
		sh_move_down(shell);
	while (shell->term->cursor.abs_pos < shell->read->buffer.display_length)
		sh_move_right(shell);
	sh_debug(shell, "after move end");
}
