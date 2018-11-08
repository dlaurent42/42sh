/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:08:27 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 22:35:13 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void		job_mark_as_running(t_job *job)
{
	t_process		*p;

	p = job->first_process;
	job->notified = 0;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
}

static void		job_message_continued(t_job *job)
{
	t_process		*p;

	job->notified = 1;
	p = job->first_process;
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(job->id, 2);
	ft_putstr_fd("] ", 2);
	ft_putnbr_fd(job->pgid, 2);
	ft_putstr_fd(" continued\n", 2);
}

void			job_continue(t_job *job, int foreground)
{
	job_mark_as_running(job);
	job_message_continued(job);
	if (foreground)
		put_job_in_foreground(job, 1);
	else
		put_job_in_background(job, 1);
}
