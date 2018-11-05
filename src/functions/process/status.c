/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:15:58 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 17:46:22 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <errno.h>

int		process_status(pid_t pid, int status)
{
	t_job		*job;
	t_process	*p;

	if (pid > 0)
	{
		job = g_sh->job;
		while (job)
		{
			p = job->first_process;
			while (p)
			{
				if (p->pid == pid)
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
				p = p->next;
			}
			job = job->next;
		}
		fprintf(stderr, "No child process %d.\n", pid);
		return (-1);
	}
	else if (pid == 0 || errno == ECHILD) /* No processes ready to report.  */
		return (-1);
	else
	{
    	/* Other weird errors.  */
		perror("waitpid");
		return (-1);
	}
}
