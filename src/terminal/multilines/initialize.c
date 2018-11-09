/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:26:25 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 17:26:31 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_reset_sh(t_shell *sh)
{
	bool	subshell;

	subshell = sh->modes.subshell;
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
	(!subshell) ? sh_set_prompt(sh) : 0;
	(!subshell) ? sh_print_prompt(sh) : 0;
}

static char	*sh_multiline_assess_status(char status)
{
	char	*ret;

	ret = "?";
	(status == STATUS_DQUOTE) ? ret = ("dquote") : 0;
	(status == STATUS_SQUOTE) ? ret = ("squote") : 0;
	(status == STATUS_BQUOTE) ? ret = ("bquote") : 0;
	(status == STATUS_HEREDOC) ? ret = ("heredoc") : 0;
	(status == STATUS_PIPE) ? ret = ("pipe") : 0;
	(status == STATUS_SUBSHELL) ? ret = ("subshell") : 0;
	(status == STATUS_NEWLINE) ? ret = ("newline") : 0;
	return (ret);
}

static void	sh_multilines_prompt(t_shell *sh, char status)
{
	(sh->prompt.content) ? ft_strdel(&sh->prompt.content) : 0;
	sh->prompt.content = ft_strjoins(
							sh_multiline_assess_status(status),
							MULT_PROMPT);
	sh->prompt.len = 3 + ft_strlens(sh_multiline_assess_status(status));
	if (sh->modes.subshell)
	{
		sh->prompt.content = ft_strjoinf("subsh ", sh->prompt.content, 2);
		sh->prompt.len += 6;
	}
	sh->prompt.len_mod = sh->prompt.len % sh->window.width;
	sh->prompt.rows = sh->prompt.len / sh->window.width + 1;
	sh_print_prompt(sh);
}

static void	sh_multiline_buffer(t_shell *sh, char status)
{
	int		i;
	size_t	len;

	i = sh->buffer.ushift - 1;
	len = ft_strlens(sh->buffer.content);
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	if (status == STATUS_HEREDOC && sh->buffer.ushift)
		while (sh->buffer.content[++i])
			sh->buffer.content[i] = '\0';
	else if (status == STATUS_BQUOTE)
		sh->buffer.content[len] = ';';
	else if (status != STATUS_NEWLINE)
		sh->buffer.content[len] = '\n';
	else
		sh->buffer.content[len - 1] = '\0';
	sh->buffer.display_len = ft_strlenu(sh->buffer.content);
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content);
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
