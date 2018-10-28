/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 22:12:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 16:07:09 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	sh_heredoc expect heredoc to be malloced and valid
**
**	sh_heredoc status codes
**		-1						: fatal error occured
**		0						: all keywords are closed -> go parser
**		LEXER_STATUS_HEREDOC (4): need to go multilines
**
**	examples:
**		cat<<toto	->	heredoc = toto
**		cat << toto	->	heredoc = toto
**		cat <<		-> 	function not called
**		cat <<>		->	function not called
*/

char		sh_heredoc(t_shell *sh, char *heredoc)
{
	if ((heredoc == NULL || heredoc[0] == '\0') && sh->modes.heredoc == FALSE)
	{
		ft_printf("sh_heredoc [1]: exit on error\n");
		return (-1);
	}
	if (sh->modes.heredoc == FALSE)
	{
		ft_printf("sh_heredoc [2]: init\n");
		return (sh_heredoc_init(sh, heredoc));
	}
	if (sh->modes.heredoc == TRUE && heredoc)
	{
		ft_printf("sh_heredoc [3]: add\n");
		return (sh_heredoc_add(sh, heredoc));
	}
	ft_printf("sh_heredoc [4]: update\n");
	return (sh_heredoc_update(sh));
}
