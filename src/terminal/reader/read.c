/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/20 23:56:16 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_arrows_dispatcher(t_shell *sh)
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

static void	sh_read_dispatcher(t_shell *sh)
{
	if (sh->read->line[0] == 27 && sh->read->line[1] == 91)
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
		read(0, sh->read->line, 4);
		if (sh->read->line[0] == 4)
			break ;
		sh_read_dispatcher(sh);
		bzero(sh->read->line, 5);
	}
}
