/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:39:32 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/10 15:19:55 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <errno.h>

void		job_launch(t_job *job, int foreground)
{
	t_process		*p;
	pid_t			pid;
	int				std[3];

	redir_load_job(job, g_sh->redir);
	std[0] = job->fd[0];
	std[1] = job->fd[1];
	std[2] = job->fd[2];
	p = job->first_process;
	while (p)
	{
		if ((pid = fork()) == -1)
			return (job_error(job, 0));
		else if (pid == 0)
			process_launch(p, job->pgid, std, foreground);
		else
		{
			p->pid = pid;
			(!job->pgid) ? job->pgid = pid : (0);
			setpgid(pid, job->pgid);
		}
		p = p->next;
	}
	redir_destroy(&g_sh->redir);
	job_message(job, "launched");
	(foreground) ?
		put_job_in_foreground(job, 0) : put_job_in_background(job, 0);
}
