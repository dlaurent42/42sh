/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:27:08 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 10:32:33 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		update_status(void)
{
	int		status;
	pid_t	pid;

	pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
	while (!process_status(pid, status))
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
}

static void		shift_jobs(t_job *last, t_job *next)
{
	if (last)
		last->next = next;
	else
		g_sh->job = next;
}

void			job_notification(void)
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
			shift_jobs(last, next);
			job_delete(job);
		}
		else
		{
			(job_is_stopped(job) && !job->notified)
				? job_message_suspended(job) : (0);
			last = job;
		}
		job = next;
	}
}
