/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   continue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 18:08:27 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/06 18:10:46 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	job_mark_as_running(t_job *job)
{
	t_process		*p;

	p = job->first_process;
	while (p)
	{
		p->stopped = 0;
		p = p->next;
	}
}

void		job_continue(t_job *job, int foreground)
{
	job_mark_as_running(job);
	if (foreground)
		put_job_in_foreground(job, 1);
	else
		put_job_in_background(job, 1);
}
