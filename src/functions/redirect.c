/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:59:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/28 17:00:48 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_dispatcher(t_shell *sh)
{
	if (sh->buffer.content[0] == 'c' && sh->buffer.content[1] == 'd')
		return (sh_cd(sh, sh->buffer.content + 3));
	return (0);
}

static void	sh_reset_sh(t_shell *sh)
{
	ft_bzero(sh->buffer.content, sh->buffer.display_len);
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
	sh->buffer.cmd = NULL;
	ft_bzero((void *)sh->read, sizeof(t_read));
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	ft_bzero((void *)&sh->modes, sizeof(t_modes));
}

void		sh_command_run(t_shell *sh)
{
	sh_move_end(sh);
	ft_putchar('\n');
	sh->prompt.last_exec_succeed = (sh->buffer.display_len)
		? sh_command_dispatcher(sh) : 0;
	(sh->buffer.display_len) ? command_add(sh) : 0;
	sh_reset_sh(sh);
}
