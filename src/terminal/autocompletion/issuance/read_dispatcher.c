/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:23:53 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:27:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			auto_arrows_dispatcher(t_ac *ac)
{
	char			*line;

	line = ac->shell->read->line;
	ac->del_file_name = ac->select->data.str;
	if (line[2] == 65 || line[2] == 90)
		auto_move_up(ac);
	else if (line[2] == 66 || line[0] == 9)
		auto_move_down(ac);
	else if (line[2] == 67)
		auto_move_right(ac);
	else if (line[2] == 68)
		auto_move_left(ac);
}

void				auto_read_dispatcher(t_ac *ac)
{
	t_shell			*shell;
	char			*line;

	shell = ac->shell;
	line = ac->shell->read->line;
	if (line[0] == 9 || (line[0] == 27 && line[1] == 91))
		auto_arrows_dispatcher(ac);
	else
	{
		if (sh_is_delete_combination(line))
			sh_deletion_dispatcher(ac->shell);
		else if (line[0] == 10)
			auto_manage_buffer(ac->shell,
					(ac->select->data.dir) ? "/" : " ");
		else
			sh_fill_buffer(shell);
		auto_clear_selection_screen(ac);
		ac->shell->modes.auto_completion = 0;
	}
}
