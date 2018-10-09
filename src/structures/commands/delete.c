/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:11:47 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/08 17:41:19 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		command_delete_by_id(t_shell *sh, unsigned int id)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	if (!(sh->cmd))
		return ;
	cmd = sh->cmd->last;
	while (cmd && cmd->id != id)
		cmd = cmd->prev;
	if (!cmd)
		return ;
	(cmd == cmd->last) ? cmd->last = cmd->next : 0;
	(cmd == sh->cmd) ? sh->cmd = cmd->prev : 0;
	(cmd->next) ? cmd->next->prev = cmd->prev : 0;
	(cmd->prev) ? cmd->prev->next = cmd->next : 0;
	tmp = cmd->next;
	ft_memdel((void **)&cmd);
	cmd = tmp;
	while (cmd)
	{
		cmd->id--;
		cmd = cmd->next;
	}
}

void		command_delete_all(t_shell *sh)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	if (!sh->cmd)
		return ;
	cmd = sh->cmd;
	while (cmd)
	{
		tmp = cmd->next;
		(cmd) ? ft_memdel((void **)&cmd) : 0;
		cmd = tmp;
	}
	cmd = NULL;
	tmp = NULL;
	sh->cmd = NULL;
}
