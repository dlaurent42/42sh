/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_end_of_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 10:55:00 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 11:18:10 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_move_end_of_line(t_shell *shell)
{
	sh_debug(shell, "before move eol");
	while (shell->term->cursor.x < shell->term->w_width
	&& shell->term->cursor.x < (shell->read->buffer.display_length + shell->term->header.display_length + 1) % shell->term->w_width)
		sh_move_right(shell);
	sh_debug(shell, "after move eol");
}
