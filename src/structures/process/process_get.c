/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 15:32:52 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 15:50:12 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_process			*process_get(t_shell *sh, int id, pid_t pid)
{
	t_process		*process;

	process = sh->process;	
	while (process)
	{
		if (process->id == id)
			return (process);
		if (!id && process->pid == pid)
			return (process);
		process = process->next;
	}
	return (NULL);
}
