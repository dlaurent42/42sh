/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 01:07:53 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_arrows_dispatcher(t_shell *sh)
{
	if (sh->read->line[1] == 91)
	{
		if (sh->read->line[2] == 67)
			sh_move_right(sh);
		else if (sh->read->line[2] == 68)
			sh_move_left(sh);
		else if (sh->read->line[2] == 70)
			sh_move_end(sh);
		else if (sh->read->line[2] == 72)
			sh_move_home(sh);
	}
	else if (sh->read->line[1] == 27 && sh->read->line[2] == 91)
	{
		if (sh->read->line[3] == 67)
			sh_move_next_word(sh);
		else if (sh->read->line[3] == 68)
			sh_move_previous_word(sh);
	}
}

static void	sh_read_dispatcher(t_shell *sh)
{
	sh_debug(NULL, NULL, sh->read->line);
	if (sh->read->line[0] == 27)
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
		read(0, sh->read->line, 6);
		if (sh->read->line[0] == 6)
			break ;
		sh_read_dispatcher(sh);
		bzero(sh->read->line, 7);
	}
}
