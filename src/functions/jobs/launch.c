/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:39:32 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 19:39:18 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		job_launch(t_job *job, int foreground)
{
	t_process		*p;
	pid_t			pid;
	int				fd[2];
	int				std[3];

	std[0] = job->fd[0];
	p = job->first_process;
	while (p)
	{
		// for pipes
		if (p->next)
		{
			if (pipe(fd) == -1)
			{
				ft_putendl_fd("pipe error", 2);
				exit(1);
			}
			std[1] = fd[1];
		}
		else
			std[1] = job->fd[1];
		// /for pipes
		if ((pid = fork()) == -1)
		{
			ft_putendl_fd("fork error", 2);
			exit(1);
		}
		else if (pid == 0)
			process_launch(p, job->pgid, std, foreground);
		else
		{
			p->pid = pid;
			if (1) // shell is active; not sure if needed
			{
				ft_printf("p->pid = %d | job->pgid = %d");
				if (!job->pgid)
					job->pgid = pid;
				setpgid(pid, job->pgid);
			}
		}
		// Cleanup after pipes
		if (std[0] != job->fd[0])
			close(std[0]);
		if (std[1] != job->fd[1])
			close(std[1]);
		std[0] = fd[0];
		p = p->next;
	}
	job_message(job, "launched");
	ft_printf("job->pgid = %d\n", job->pgid);
	if (0) // shell is active ; not sure if needed
		job_wait(job);
	else if (foreground)
		put_job_in_foreground(job, 0);
	else
		put_job_in_background(job, 0);
}
