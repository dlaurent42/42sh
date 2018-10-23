/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:59:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/23 20:37:13 by azaliaus         ###   ########.fr       */
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

void		sh_command_run(t_shell *sh)
{
	sh_move_end(sh);
	ft_putchar('\n');
	if (sh->buffer.display_len)
	{
		ft_bzero(sh->buffer.parsed, ARG_MAX);
		ft_strcpy(sh->buffer.parsed, sh->buffer.content);
		if (sh_command_lexer(sh, sh->env, sh->buffer.parsed) == FALSE)
			return (sh_multilines(sh));
		sh->modes.multiline = FALSE;
		if (!sh_command_empty(sh->buffer.parsed))
		{
			sh->bin = bin_update(sh, sh->env, sh->bin);
			command_add(sh, true);
			sh->modes.exec = TRUE;
			sh_build_tree(sh->buffer.parsed);
			// Left for now
			sh_command_parser(
				sh,
				sh->env,
				sh->bin,
				sh->buffer.parsed);
		}
	}
	sh_reset_sh(sh);
}
