/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:59:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 00:28:57 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_command_dispatcher(t_shell *sh)
{
	char	res;

	res = 0;
	if (sh->buffer.content[0] == 'c' && sh->buffer.content[1] == 'd')
		res = sh_cd(sh, sh->buffer.content + 3);
	else if (sh->buffer.content[0] == 'e' && sh->buffer.content[1] == 'x'
	&& sh->buffer.content[2] == 'i' && sh->buffer.content[3] == 't')
		sh_exit(sh, sh->buffer.content + 5);
	else if (sh->buffer.content[0] == 's' && sh->buffer.content[1] == 'e'
	&& sh->buffer.content[2] == 't' && sh->buffer.content[3] == 'e'
	&& sh->buffer.content[4] == 'n' && sh->buffer.content[5] == 'v')
		res = sh_setenv(sh, sh->buffer.content + 7);
	else if (sh->buffer.content[0] == 'u' && sh->buffer.content[1] == 'n'
	&& sh->buffer.content[2] == 's' && sh->buffer.content[3] == 'e'
	&& sh->buffer.content[4] == 't' && sh->buffer.content[5] == 'e'
	&& sh->buffer.content[6] == 'n' && sh->buffer.content[7] == 'v')
		res = sh_unsetenv(sh, sh->buffer.content + 9);
	else if (!ft_strcmps(sh->buffer.content, "history"))
		sh_history(sh);
	return (res);
}

static void	sh_reset_sh(t_shell *sh)
{
	ft_bzero(sh->buffer.content, sh->buffer.unicode_len);
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
	sh->buffer.cmd = NULL;
	sh->read->unicode_bytes_left = 0;
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	ft_bzero((void *)&sh->modes, sizeof(t_modes));
	sh_set_prompt(sh);
	sh_print_prompt(sh);
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
