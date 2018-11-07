/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:15:58 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/07 14:28:34 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <errno.h>

/*
**	When errno == ECHILD - there is no process to get.
*/

static int	process_status_err(pid_t pid)
{
	if (pid == 0 || errno == ECHILD)
		return (-1);
	ft_putendl_fd("waitpid error", 2);
	return (-1);
}

static int	process_found(t_process *p, int status)
{
	p->status = status;
	if (WIFSTOPPED(status))
		p->stopped = 1;
	else
	{
		p->completed = 1;
		if (WIFSIGNALED(status))
			ft_putendl_fd("Terminated by singal!", 2);
	}
	return (0);
}

int			process_status(pid_t pid, int status)
{
	t_job		*job;
	t_process	*p;

	if (pid <= 0)
		return (process_status_err(pid));
	job = g_sh->job;
	while (job)
	{
		p = job->first_process;
		while (p)
		{
			if (p->pid == pid)
				return (process_found(p, status));
			p = p->next;
		}
		job = job->next;
	}
	ft_putendl_fd("NO child process", 2);
	return (-1);
}
