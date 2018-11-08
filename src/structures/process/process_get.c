/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_get.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 15:32:52 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/08 22:18:34 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_process			*process_get(t_shell *sh, pid_t pid)
{
	t_process		*process;

	process = sh->process;
	while (process)
	{
		if (process->pid == pid)
			return (process);
		process = process->next;
	}
	return (NULL);
}
