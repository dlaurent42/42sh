/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:14:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 12:10:13 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_heredoc_get_next(t_shell *sh)
{
	char		*returned;
	t_heredocs	*next;

	returned = NULL;
	if (!sh->heredocs)
		return (NULL);
	if (!(returned = ft_strdups(sh->heredocs->value)))
		returned = ft_strdups("");
	ft_strdel(&sh->heredocs->value);
	ft_strdel(&sh->heredocs->keyword);
	next = sh->heredocs->next;
	free(sh->heredocs);
	sh->heredocs = next;
	return (returned);
}
