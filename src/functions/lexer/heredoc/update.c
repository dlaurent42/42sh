/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:02:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 16:02:55 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_heredoc_update_close(t_shell *sh, t_heredocs *heredocs)
{
	heredocs->closed = TRUE;
	if (!heredocs->next)
	{
		ft_strdel(&sh->buffer.parsed);
		ft_bzero(
			(void *)(sh->buffer.content + sh->buffer.ushift),
			ARG_MAX);
		sh->buffer.parsed = ft_strdups(sh->buffer.content);
		return (STATUS_OK);
	}
	return (STATUS_HEREDOC);
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
	if (ft_strcmps(sh->buffer.content + sh->buffer.ushift, tmp->keyword) == 0)
		return (sh_heredoc_update_close(sh, tmp));
	tmp->value = ft_strjoinf(
		tmp->value,
		sh->buffer.content + sh->buffer.ushift,
		1);
	tmp->value = ft_strjoinf(
		tmp->value,
		"\n",
		1);
	if (ft_strlens(tmp->value) >= ARG_MAX)
		tmp->value[0] = '\0';
	return (STATUS_HEREDOC);
}
