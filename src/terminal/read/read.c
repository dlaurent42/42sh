/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 04:57:07 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_arrows_dispatcher(t_shell *sh)
{
	char	*line;

	line = sh->read->line;
	(line[1] == 91 && line[2] == 67) ? sh_move_right(sh) : 0;
	(line[1] == 91 && line[2] == 68) ? sh_move_left(sh) : 0;
	(line[1] == 91 && line[2] == 70) ? sh_move_end(sh) : 0;
	(line[1] == 91 && line[2] == 72) ? sh_move_home(sh) : 0;
	(line[1] == 27 && line[2] == 91 && line[3] == 67)
		? sh_move_next_word(sh) : 0;
	(line[1] == 27 && line[2] == 91 && line[3] == 68)
		? sh_move_previous_word(sh) : 0;
	(ft_strcmps(sh->read->line, "\x1b\x5b\x31\x3b\x32\x44") == 0)
		? sh_select_left_char(sh) : 0;
	(ft_strcmps(sh->read->line, "\x1b\x5b\x31\x3b\x32\x43") == 0)
		? sh_select_right_char(sh) : 0;
	(ft_strcmps(sh->read->line, "\x1b\x5b\x31\x3b\x31\x30\x44") == 0)
		? sh_select_left_word(sh) : 0;
	(ft_strcmps(sh->read->line, "\x1b\x5b\x31\x3b\x31\x30\x43") == 0)
		? sh_select_right_word(sh) : 0;
}

static void	sh_read_dispatcher(t_shell *sh)
{
	//sh_debug(NULL, NULL, sh->read->line);
	if (sh->modes.select
	&& !(sh->read->line[0] == 3
	|| ft_strcmps(sh->read->line, "\x1b\x5b\x31\x3b\x32\x43") == 0
	|| ft_strcmps(sh->read->line, "\x1b\x5b\x31\x3b\x32\x44") == 0
	|| ft_strcmps(sh->read->line, "\x1b\x5b\x31\x3b\x31\x30\x43") == 0
	|| ft_strcmps(sh->read->line, "\x1b\x5b\x31\x3b\x31\x30\x44") == 0))
		sh_unselect(sh);
	if (sh->read->line[0] == 3)
		sh_copy_selection(sh);
	else if (sh->read->line[0] == 27)
		sh_arrows_dispatcher(sh);
	else if (sh->read->line[0] == 127)
		sh_read_delete(sh);
	else if (sh->read->line[0] == 9)
		sh_read_autocompletion(sh);
	else
		sh_fill_buffer(sh);
}

void		sh_read(t_shell *sh)
{
	while (TRUE)
	{
		(sh->modes.display) ? 0 : sh_print_prompt(sh);
		read(0, sh->read->line, 7);
		if (sh->read->line[0] == 4)
			break ;
		sh_read_dispatcher(sh);
		bzero(sh->read->line, 8);
	}
}
