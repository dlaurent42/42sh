/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_beginning_of_block.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 15:07:10 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sh_move_home(t_shell *shell)
{
	unsigned char	i;

	i = 0;
	sh_debug(shell, "before move start");
	if (shell->term->cursor.abs_pos == 0)
		return ;
	while (shell->term->cursor.y)
		sh_move_up(shell);
	sh_move_beginning_of_line(shell);
	sh_debug(shell, "after move start");
}
