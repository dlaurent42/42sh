/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:26:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/02 14:27:33 by dlaurent         ###   ########.fr       */
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

static char	*sh_multiline_assess_status(char status)
{
	if (status == STATUS_DQUOTE)
		return ("dquote");
	if (status == STATUS_SQUOTE)
		return ("squote");
	if (status == STATUS_BQUOTE)
		return ("bquote");
	if (status == STATUS_HEREDOC)
		return ("heredoc");
	if (status == STATUS_PIPE)
		return ("pipe");
	if (status == STATUS_SUBSHELL)
		return ("subshell");
	if (status == STATUS_NEWLINE)
		return ("newline");
	return ("?");
}

static void	sh_multilines_prompt(t_shell *sh, char status)
{
	(sh->prompt.content) ? ft_strdel(&sh->prompt.content) : 0;
	sh->prompt.content = ft_strjoins(
							sh_multiline_assess_status(status),
							MULT_PROMPT);
	sh->prompt.len = 3 + ft_strlens(sh_multiline_assess_status(status));
	sh->prompt.len_mod = sh->prompt.len % sh->window.width;
	sh->prompt.rows = sh->prompt.len / sh->window.width + 1;
	sh_print_prompt(sh);
}

static void	sh_multiline_buffer(t_shell *sh, char status)
{
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	if (status != STATUS_NEWLINE)
	{
		sh->buffer.content[sh->buffer.unicode_len + sh->buffer.ushift] = '\n';
		sh->buffer.display_len += sh->buffer.dshift + 1;
		sh->buffer.unicode_len += sh->buffer.ushift + 1;
	}
	else
	{
		sh->buffer.content[
			sh->buffer.unicode_len
			+ sh->buffer.ushift
			- 1] = '\0';
		sh->buffer.display_len += sh->buffer.dshift - 1;
		sh->buffer.unicode_len += sh->buffer.ushift - 1;
	}
	sh->buffer.dshift = sh->buffer.display_len;
	sh->buffer.ushift = sh->buffer.unicode_len;
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
}

void		sh_multilines(t_shell *sh, char status)
{
	ft_strdel(&sh->buffer.parsed);
	if (ft_strlens(sh->buffer.content) >= ARG_MAX)
		return (sh_reset_sh(sh));
	sh_multiline_buffer(sh, status);
	sh->modes.multiline = TRUE;
	sh_multilines_prompt(sh, status);
}
