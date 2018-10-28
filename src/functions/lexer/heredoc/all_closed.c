/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 17:08:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 17:22:36 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	sh_heredocs_all_close(t_shell *sh)
{
	t_heredocs	*tmp;

	if (!sh->heredocs || sh->modes.heredoc == FALSE)
		return (TRUE);
	if (!(tmp = sh->heredocs))
		return (TRUE);
	while (tmp && tmp->closed)
		tmp = tmp->next;
	if (tmp)
		return (FALSE);
	return (TRUE);
}
