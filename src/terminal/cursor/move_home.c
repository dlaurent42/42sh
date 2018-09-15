/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_home.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/15 22:25:14 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_move_home(t_shell *shell)
{
	while (shell->term->cursor.y)
	{
		ft_putstr(K_UP);
		shell->term->cursor.y--;
	}
	ft_putstr(K_COL_0);
	shell->term->cursor.x = 0;
	while (shell->term->cursor.x < shell->term->prompt.display_length_mod)
	{
		ft_putstr(K_RIGHT);
		shell->term->cursor.x++;
	}
	shell->term->cursor.x = 0;
	shell->term->cursor.y = 0;
	shell->term->cursor.abs_pos = 0;
	shell->term->cursor.rel_pos = 0;
}
