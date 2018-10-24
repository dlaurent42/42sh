/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:59:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 12:50:56 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_reset_sh(t_shell *sh)
{
	ft_bzero(sh->buffer.content, sh->buffer.unicode_len + sh->buffer.ushift);
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
	sh->buffer.dshift = 0;
	sh->buffer.ushift = 0;
	sh->buffer.cmd = NULL;
	sh->read->unicode_bytes_left = 0;
	sh->pid = 0;
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	ft_bzero((void *)&sh->modes, sizeof(t_modes));
	sh_set_prompt(sh);
	sh_print_prompt(sh);
}

static char	sh_command_lexer_parser(t_shell *sh)
{
	char	status;

	status = 0;
	if ((status = sh_command_lexer(sh, sh->env, sh->buffer.parsed)) != 0)
		return (status);
	sh->modes.multiline = FALSE;
	if (!sh_command_empty(sh->buffer.parsed))
	{
		sh->bin = bin_update(sh, sh->env, sh->bin);
		command_add(sh, true);
		sh->modes.exec = TRUE;
		sh_command_parser(
			sh,
			sh->env,
			sh->bin,
			sh->buffer.parsed);
	}
	return (status);
}

void		sh_command_run(t_shell *sh)
{
	char	status;

	status = 0;
	sh_move_end(sh);
	ft_putchar('\n');
	ft_strdel(&sh->buffer.parsed);
	sh->buffer.parsed = ft_strdups(sh->buffer.content);
	if (sh->buffer.display_len)
		if ((status = sh_command_lexer_parser(sh)) > 0)
			return (sh_multilines(sh, status));
	sh_reset_sh(sh);
}
