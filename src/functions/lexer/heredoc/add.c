/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:50:36 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 18:40:47 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_heredoc_add(t_shell *sh, char *heredoc)
{
	t_heredocs	*tmp;
	t_heredocs	*new;

	tmp = sh->heredocs;
	if (tmp)
		while (tmp->next)
			tmp = tmp->next;
	if (!(new = (t_heredocs *)ft_memalloc(sizeof(t_heredocs))))
		return (-1);
	new->keyword = ft_strdups(heredoc);
	(!sh->heredocs) ? sh->heredocs = new : 0;
	(tmp) ? tmp->next = new : 0;
	sh->modes.heredoc = TRUE;
	return (STATUS_HEREDOC);
}
