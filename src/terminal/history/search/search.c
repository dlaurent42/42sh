/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:58:09 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 19:02:16 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_history_nosearch(t_shell *sh)
{
	ft_bzero(sh->buffer.content + sh->buffer.ushift, ARG_MAX);
	ft_strcpy(sh->buffer.content + sh->buffer.ushift, sh->buffer.stored);
	sh->search.match = NULL;
}

static void	sh_history_search_assign(t_shell *sh, t_cmd *match, char *search)
{
	ft_strdel(&search);
	if (!match)
		return (sh_history_nosearch(sh));
	ft_bzero(sh->buffer.content + sh->buffer.ushift, ARG_MAX);
	ft_strcpy(sh->buffer.content + sh->buffer.ushift, match->content);
	sh->search.match = match;
}

void		sh_history_perform_search(t_shell *sh)
{
	int		current;
	int		occurences;
	char	*search;
	t_cmd	*cmd;
	t_cmd	*match;

	occurences = 0;
	match = NULL;
	if (sh->search.content[0] == '\0' || !(cmd = sh->cmd))
		return (sh_history_nosearch(sh));
	search = ft_strjoins("*", sh->search.content);
	search = ft_strjoinf(search, "*", 1);
	while (cmd)
	{
		current = nmatch(cmd->content, search);
		if (current > occurences)
		{
			match = cmd;
			occurences = current;
		}
		cmd = cmd->next;
	}
	sh_history_search_assign(sh, match, search);
}
