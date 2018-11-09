/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:23:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/07 17:12:28 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			auto_arrows_dispatcher(t_shell *sh)
{
	char			*line;

	line = sh->read->line;
	sh->ac->del_file_name = sh->ac->select->data.escaped_str;
	if (line[2] == 65 || line[2] == 90)
		auto_move_up(sh);
	else if (line[2] == 66 || line[0] == 9)
		auto_move_down(sh);
	else if (line[2] == 67)
		auto_move_right(sh);
	else if (line[2] == 68)
		auto_move_left(sh);
}

void				auto_read_dispatcher(t_shell *sh)
{
	char			*line;

	line = sh->read->line;
	if (line[0] == 9 || (line[0] == 27 && line[1] == 91))
		auto_arrows_dispatcher(sh);
	else
	{
		if (sh_is_delete_combination(line))
			sh_deletion_dispatcher(sh);
		else if (line[0] == 10)
		{
			if (sh->ac->select->data.dir)
				sh_print_str(sh, "/");
			else if (sh->ac->select->data.env && sh->ac->auto_mode != AUTO_ENV)
				sh_print_str(sh, "=");
			else
				sh_print_str(sh, " ");
		}
		else if (sh->read->line[0] != 4)
			sh_fill_buffer(sh);
		auto_clear_selection_screen(sh);
		sh->modes.auto_completion = FALSE;
	}
}
