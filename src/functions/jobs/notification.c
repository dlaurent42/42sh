/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:27:08 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/06 17:49:50 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
  	while (!process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED|WNOHANG);
}

void		job_notification(void)
{
	t_job		*job;
	t_job		*last;
	t_job		*next;

	update_status();
	job = g_sh->job;
	last = NULL;
	while (job)
	{
		next = job->next;
		if (job_is_completed(job))
		{
			job_message(job, "done");
			if (last)
				last->next = next;
			else
				g_sh->job = next;
			job_delete(job);
			signal_catching();
		}
		else if (job_is_stopped(job) && !job->notified)
		{
        	job_message(job, "suspended");
			job->notified = 1;
			last = job;
		}
		else
        	last = job;
		job = next;
	}
}
