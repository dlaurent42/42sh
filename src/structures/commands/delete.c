/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:11:47 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 20:06:37 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
