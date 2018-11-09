/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:10:04 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/09 13:16:01 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job				*get_latest_job(t_shell *sh)
{
	t_job			*job;

	job = sh->job;
	while (jobs && job->next)
		job = job->next;
	return (job);
}

char				buildin_jobs_launch(t_shell *sh, char **argv, int mode)
{
	t_job		*job;

	job = sh->job;
	if (!ft_count_argv((void **)argv))
		job = get_latest_job(sh);
	else
		job = sh->jobs;
	if (!job)
		ft_putendl("bg: no current job");
	else
	{
		if (!ft_count_argv((void **)argv))
		{
			while (job->next)
				job = job->next;
			job_continue(job, mode); // <- 1 - foreground | 0 - background
		}
		else if (ft_count_argv((void **)argv) == 1)
		{
			// Dav: do stuff
			// Return proper job and run this
			job_continue(job, mode); // <- 1 - foreground | 0 - background
		}
		else
		{
			ft_putendl("fg: too much arguments");
			return (STATUS_OK);
		}
	}
	return (STATUS_OK);
	// return (jobs_finder(sh, argv, JOBS_BG));
}
