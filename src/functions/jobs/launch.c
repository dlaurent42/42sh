/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:39:32 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/06 09:02:14 by azaliaus         ###   ########.fr       */
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
	std[2] = job->fd[2];
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
			ft_printf("p->pid = %d\n", p->pid);
			(!job->pgid) ? job->pgid = pid : (0);
			setpgid(pid, job->pgid);
		}
		(std[0] != job->fd[0]) ? close(std[0]) : (0);
		(std[1] != job->fd[1]) ? close(std[1]) : (0);
		std[0] = fd[0];
		p = p->next;
	}
	job_message(job, "launched");
	ft_printf("job->pgid = %d\n", job->pgid);
	if (0) // shell is not active ; not sure if needed
		job_wait(job);
	else if (foreground)
		put_job_in_foreground(job, 0);
	else
		put_job_in_background(job, 0);
}
