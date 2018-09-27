/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/01 16:10:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 14:09:28 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
