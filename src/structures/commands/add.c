/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 21:35:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 20:06:20 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		command_add(t_shell *sh, char *command)
{
	t_cmd	*new;

	if (!command)
		return ;
	if (!(new = (t_cmd *)ft_memalloc(sizeof(t_cmd))))
		return ;
	new->id = (sh->cmd) ? sh->cmd->id + 1 : 1;
	ft_strcpy(new->cmd, command);
	new->len = ft_strlens(command);
	new->next = (sh->cmd) ? sh->cmd : NULL;
	new->last = (sh->cmd) ? sh->cmd->last : new;
	(sh->cmd) ? sh->cmd->prev = new : 0;
	sh->cmd = new;
}
