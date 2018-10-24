/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:02:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 14:07:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_heredoc_update_close(t_shell *sh, t_heredocs *heredocs)
{
	heredocs->closed = TRUE;
	if (!heredocs->next)
		return (0);
	return (1);
}

char		sh_heredoc_update(t_shell *sh)
{
	t_heredocs	*tmp;

	if (!(tmp = sh->heredocs))
		return (-1);
	while (tmp->closed)
		tmp = tmp->next;
	if (!tmp)
		return (-1);
	if (ft_strcmps(sh->buffer.parsed + sh->buffer.ushift, tmp->keyword) == 0)
		return (sh_heredoc_update_close(sh, tmp));
	tmp->keyword = ft_strjoinf(
		tmp->keyword,
		sh->buffer.content + sh->buffer.ushift,
		1);
	return (1);
}
