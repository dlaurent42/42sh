/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:26:25 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 16:06:03 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Adds process to head of the list.
*/

bool				process_add(t_shell *sh, pid_t pid, t_cmd *cmd)
{
	t_process		*new_process;

	if (!(new_process = process_new()))
		return (false);
	new_process->id = (sh->process) ? sh->process->id + 1 : 1;
	new_process->status = 0;//WHAT SHOULD THIS BE?
	new_process->pid = pid;
	new_process->cmd = cmd;
	new_process->next = sh->process;
	sh->process = new_process;
	return (true);
}
