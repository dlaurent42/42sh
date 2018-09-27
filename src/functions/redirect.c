/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:59:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 19:37:19 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_command_run(t_shell *sh)
{
	(sh->buffer.display_len) ? command_add(sh, sh->buffer.content) : 0;
	sh->modes.select = FALSE;
	sh->modes.display = FALSE;
	sh_move_end(sh);
	ft_putchar('\n');
	ft_bzero(sh->buffer.content, sh->buffer.display_len);
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
	sh->buffer.cmd = NULL;
	ft_memset((void *)sh->read, 0, sizeof(t_read));
	ft_memset((void *)&sh->cursor, 0, sizeof(t_cursor));
}
