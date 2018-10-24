/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 22:12:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 10:20:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int

static char	sh_heredoc_has_any(t_shell *sh)
{
	int		i;
	int		res;
	bool	in_dquote;
	bool	in_squote;	

	i = 0;
	res = 0;
	in_dquote = FALSE;
	in_squote = FALSE;
	while (sh->buffer.content[i] && res >= 0)
	{
		if (sh->buffer.content[i] == '"' && !glob_is_esc(sh->buffer.content, i))
			in_dquote = (in_dquote || in_squote) ? FALSE : TRUE;
		else if (sh->buffer.content[i] == '\'' && !glob_is_esc(sh->buffer.content, i))
			in_squote = (in_dquote || in_squote) ? FALSE : TRUE;
		else if (sh->buffer.content[i] == '<' && sh->buffer.content[i + 1] == '<'
		&& sh->buffer.content[i + 1]
			res = sh_heredoc_add(sh, i + 2);
		i++;
	}
	return (res);
}

char		sh_heredoc(t_shell *sh)
{
	if (!sh->modes.heredoc)
		return (!sh_heredoc_has_any(sh));
	return (sh_heredoc_update(sh));
}
