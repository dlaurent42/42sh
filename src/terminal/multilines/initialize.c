/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:26:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 14:23:31 by dlaurent         ###   ########.fr       */
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
	ft_strdel(&sh->buffer.parsed);
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	ft_bzero((void *)&sh->modes, sizeof(t_modes));
	sh_set_prompt(sh);
	sh_print_prompt(sh);
}

static int	sh_multilines_assess_status_len(char status)
{
	if (status == STATUS_DQUOTE
	|| status == STATUS_SQUOTE
	|| status == STATUS_BQUOTE)
		return (6);
	if (status == STATUS_HEREDOC)
		return (7);
	if (status == STATUS_PIPE)
		return (4);
	if (status == STATUS_PARENTHESIS)
		return (11);
	if (status == STATUS_SQUARE)
		return (14);
	if (status == STATUS_CURLY)
		return (13);
	return (1);
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
	if (status == STATUS_PARENTHESIS)
		return ("parenthesis");
	if (status == STATUS_SQUARE)
		return ("square-bracket");
	if (status == STATUS_CURLY)
		return ("curly-braces");
	return ("?");
}

static void	sh_multilines_prompt(t_shell *sh, char status)
{
	(sh->prompt.content) ? ft_strdel(&sh->prompt.content) : 0;
	sh->prompt.content = ft_strjoins(
							sh_multiline_assess_status(status),
							MULT_PROMPT);
	sh->prompt.len = 3 + sh_multilines_assess_status_len(status);
	sh->prompt.len_mod = sh->prompt.len % sh->window.width;
	sh->prompt.rows = sh->prompt.len / sh->window.width + 1;
	sh_print_prompt(sh);
}

void		sh_multilines(t_shell *sh, char status)
{
	ft_strdel(&sh->buffer.parsed);
	if (ft_strlens(sh->buffer.content) < ARG_MAX)
		sh->buffer.content[sh->buffer.unicode_len + sh->buffer.ushift] = '\n';
	else
		return (sh_reset_sh(sh));
	sh->modes.multiline = TRUE;
	sh_multilines_prompt(sh, status);
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	sh->buffer.display_len += sh->buffer.dshift + 1;
	sh->buffer.unicode_len += sh->buffer.ushift + 1;
	sh->buffer.dshift = sh->buffer.display_len;
	sh->buffer.ushift = sh->buffer.unicode_len;
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
}
