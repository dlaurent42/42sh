/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/06 15:25:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_arrows_dispatcher(t_shell *shell)
{
	if (shell->read->line[2] == 67)
		sh_move_right(shell);
	else if (shell->read->line[2] == 68)
		sh_move_left(shell);
	else if (shell->read->line[2] == 70)
		sh_move_end(shell);
	else if (shell->read->line[2] == 72)
		sh_move_start(shell);
}

static void	sh_read_dispatcher(t_shell *shell)
{
	if (shell->read->line[0] == 27 && shell->read->line[1] == 91)
		sh_arrows_dispatcher(shell);
	else if (shell->read->line[0] == 127)
		sh_read_delete(shell);
	else if (shell->read->line[0] == 9)
		sh_read_autocompletion(shell);
	else
		sh_fill_buffer(shell);
}

void		sh_read(t_shell *shell)
{
	while (TRUE)
	{
		sh_print_header(shell);
		read(0, shell->read->line, 3);
		if (shell->read->line[0] == 4)
			break ;
		sh_read_dispatcher(shell);
		bzero(shell->read->line, 4);
	}
}
