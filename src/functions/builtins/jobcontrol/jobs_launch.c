/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:10:04 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/09 14:12:17 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_process			*get_process_by_pid(t_job *job, pid_t pid)
{
	t_process		*process;

	process = NULL;
	while (job)
	{
		proces = job->first_process;
		while (process)
		{
			if (process->pid = pid)
			   return (process);	
			process = process->next;
		}
		job = job->next;
	}
	return (process);
}

t_job				*get_job_by_id(t_job *job, int id)
{
	while (job)
	{
		if (job->id = id)
			break ;
		job = job->next;
	}
	return (job);
}

t_job				*get_latest_job(t_job *job)
{
	while (jobs && job->next)
		job = job->next;
	return (job);
}

char				buildin_jobs_launch(t_shell *sh, char **argv, int mode)
{
	t_job		*job;

	job = sh->job;
	if (!ft_count_argv((void **)argv))
		job = get_latest_job(job);
	else if (!ft_count_argv((void **)argv) == 2)
	{
		if (!ft_strcmps(argv[0], "-i"))
			job = job_by_id(job, ft_atoi(argv[1]));
	}
	else
		job = sh->jobs;
	if (!job)
		ft_printf("%s: no jobs\n", (mode == JOBS_FG) ? "fg" : "bg");
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
}
