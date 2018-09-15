/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/15 22:25:13 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_move_left(t_shell *shell)
{
	unsigned char	i;

	i = 0;
	if (shell->term->cursor.abs_pos == 0)
		return ;
	if (shell->term->cursor.x > 0)
	{
		ft_putstr(K_LEFT);
		shell->term->cursor.x--;
	}
	else
	{
		while (i < shell->term->window.width)
		{
			ft_putstr(K_RIGHT);
			i++;
		}
		ft_putstr(K_UP);
		shell->term->cursor.y--;
		shell->term->cursor.x = (shell->term->cursor.y == 0)
		? shell->term->window.width - shell->term->prompt.display_length_mod - 1
		: shell->term->window.width - 1;
	}
	shell->term->cursor.abs_pos--;
	sh_set_rel_pos(shell, 1, -1);
}
