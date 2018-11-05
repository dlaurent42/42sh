/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:39:32 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 17:53:10 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		job_launch(t_job *job, int foreground)
{
	t_process		*p;
	pid_t			pid;
	int				fd[2];
	int				infile;
	int				outfile;

	infile = job->fd[0];
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
			outfile = fd[1];
		}
		else
			outfile = job->fd[0];
		// /for pipes
		if ((pid = fork()) == -1)
		{
			ft_putendl_fd("fork error", 2);
			exit(1);
		}
		else if (pid == 0)
			process_launch(p, job->pgid, job->fd, foreground);
		else
		{
			p->pid = pid;
			if (1) // shell is active; not sure if needed
			{
				if (!job->pgid)
					job->pgid = pid;
				setpgid(pid, job->pgid);
			}
		}
		// Cleanup after pipes
		if (infile != job->fd[0])
			close(infile);
		if (outfile != job->fd[1])
			close(outfile);
		infile = fd[0];
		p = p->next;
	}
	// Formatting message of launch
	ft_printf("Job is lauched!!!\nJob info:");
	ft_printf("job->pgid = %d\n", job->pgid);
	if (0) // shell is active ; not sure if needed
		; // wait_for job
	else if (foreground)
		put_job_in_foreground(job, 0);
	else
		;//put_job_in_background(j, 0);
}
