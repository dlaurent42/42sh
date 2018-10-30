/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:26:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/29 16:48:46 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	sh->modes.multiline = TRUE;
	sh_multilines_prompt(sh, status);
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	if (sh->buffer.unicode_len < ARG_MAX)
		sh->buffer.content[sh->buffer.unicode_len + sh->buffer.ushift] = '\n';
	sh->buffer.display_len += sh->buffer.dshift + 1;
	sh->buffer.unicode_len += sh->buffer.ushift + 1;
	sh->buffer.dshift = sh->buffer.display_len;
	sh->buffer.ushift = sh->buffer.unicode_len;
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
}
