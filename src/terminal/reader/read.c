/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/06 11:06:25 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// cb: empty current line from beginning to cursor
// nd: move 1 char to left
// le: move 1 char to right
// do: move 1 line down
// up: move 1 line up
// ch: move to col 0 of curr line

// co: number of columns
// li: numner of lines

// 67 : right
// 68 : left

static void	sh_read_esc(t_shell *shell)
{
	char c;

	c = shell->read->line[2];
	if (c == 65)// up arrow
		return ;
	else if (c == 66)// down arrow
		return ;
	else if (c == 67 || c == 68 || c == 70 || c == 72)
		sh_move_cursor(shell, c);
}

	if (c == 67)
		sh_move_right(shell);
	else if (c == 68)
		sh_move_left(shell);
	else if (c == 70)
		sh_move_end(shell);
	else if (c == 72)
		sh_move_start(shell);

static void	sh_arrows_dispatcher(t_shell *shell)
{
	if (shell->read->line[2] == 67
	|| shell->read->line[2] == 68
	|| shell->read->line[2] == 70
	|| shell->read->line[2] == 72)
}

static void	sh_read_dispatcher(t_shell *shell)
{
	if (shell->read->line[0] == 27 && shell->read->line[1] == 91)
		sh_read_esc(shell); // rename -> it concerns only arrows
	else if (shell->read->line[0] == 127)
		sh_read_delete(shell);
	else if (shell->read->line[0] == 9)
		sh_read_autocompletion(shell); // @dav
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
