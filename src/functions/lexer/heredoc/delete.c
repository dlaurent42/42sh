/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:38:07 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 13:49:47 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_heredoc_delete(t_shell *sh)
{
	t_heredocs	*tmp;

	if (!sh || !sh->heredocs)
		return ;
	while (sh->heredocs)
	{
		tmp = sh->heredocs->next;
		ft_strdel(&sh->heredocs->keyword);
		ft_strdel(&sh->heredocs->value);
		free(sh->heredocs);
		sh->heredocs = tmp;
	}
}
