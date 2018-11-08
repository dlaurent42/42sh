/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:26:03 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 22:09:43 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static size_t	jobs_ahead(t_job *job)
{
	size_t		ret;

	ret = 0;
	while (job)
	{
		job = job->next;
		(job) ? ret++ : (0);
	}
	return (ret);
}

static char		job_get_rank(t_job *job)
{
	char		ret;
	size_t		j_ahead;

	ret = ' ';
	j_ahead = jobs_ahead(job);
	if (j_ahead <= 1)
		ret = (j_ahead == 0 ? '+' : '-');
	return (ret);
}

static char		*job_get_status(t_job *job)
{
	if (!job)
		return (NULL);
	if (job_is_stopped(job) && !job_is_completed(job))
		return ("suspended");
	else if (job_is_completed(job))
		return ("done");
	return ("running");
}

void			jobs_display(t_job *job)
{
	char		rank;
	char		*status;

	if (!job)
		return ;
	while (job)
	{
		rank = job_get_rank(job);
		status = job_get_status(job);
		ft_printf("[%d] %c %s %s\n", job->id, rank, status, job->command);
		job = job->next;
	}
}
