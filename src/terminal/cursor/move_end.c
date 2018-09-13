/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/13 23:01:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_move_end(t_shell *shell)
{
	ft_putstr(K_COL_0);
	shell->term->cursor.x = 0;
	while (shell->term->cursor.y < (shell->read->buffer.display_length + shell->term->header.display_length_mod + 1) / shell->term->w_width)
	{
		ft_putstr(K_DOWN);
		shell->term->cursor.y++;
	}
	while ((shell->term->cursor.y && shell->term->cursor.x < (shell->read->buffer.display_length + shell->term->header.display_length_mod + 1) % shell->term->w_width)
	|| (shell->term->cursor.y == 0 && shell->term->cursor.x < shell->read->buffer.display_length + shell->term->header.display_length_mod + 1))
	{
		ft_putstr(K_RIGHT);
		shell->term->cursor.x++;
	}
	if (shell->term->cursor.y == 0)
		shell->term->cursor.x = shell->read->buffer.display_length;
	shell->term->cursor.abs_pos = shell->read->buffer.display_length;
	shell->term->cursor.rel_pos = shell->read->buffer.unicode_length;
}
