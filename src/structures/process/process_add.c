/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 14:26:25 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/08 22:20:55 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Adds process to head of the list.
*/

bool				process_add(t_shell *sh, pid_t pid)
{
	t_process		*new_process;

	if (!(new_process = process_new()))
		return (false);
	new_process->status = 0;
	new_process->pid = pid;
	new_process->next = sh->process;
	sh->process = new_process;
	return (true);
}
