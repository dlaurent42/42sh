/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:23:53 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 00:35:02 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			auto_arrows_dispatcher(t_shell *shell)
{
	char			*line;

	line = shell->read->line;
	shell->ac->del_file_name = shell->ac->select->data.str;
	if (line[2] == 65 || line[2] == 90)
		auto_move_up(shell);
	else if (line[2] == 66 || line[0] == 9)
		auto_move_down(shell);
	else if (line[2] == 67)
		auto_move_right(shell);
	else if (line[2] == 68)
		auto_move_left(shell);
}

void				auto_read_dispatcher(t_shell *shell)
{
	char			*line;

	line = shell->read->line;
	if (line[0] == 9 || (line[0] == 27 && line[1] == 91))
		auto_arrows_dispatcher(shell);
	else
	{
		if (sh_is_delete_combination(line))
			sh_deletion_dispatcher(shell);
		else if (line[0] == 10)
			auto_manage_buffer(shell,
					(shell->ac->select->data.dir) ? "/" : " ");
		else
			sh_fill_buffer(shell);
		auto_clear_selection_screen(shell);
		shell->modes.auto_completion = 0;
	}
}
