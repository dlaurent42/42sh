/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:10:04 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/09 14:57:05 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				is_valid_number(char *str)
{
	int				len;

	len = 0;
	while (*str)
	{
		if (!ft_isdigit(*str) || len > 10)
			return (false);
		len++;
		str++;
	}
	return (true);
}

t_job				*get_process_by_pid(t_job *job, pid_t pid)
{
	t_process		*process;

	process = NULL;
	while (job)
	{
		process = job->first_process;
		while (process)
		{
			if (process->pid == pid)
				return (job);
			process = process->next;
		}
		job = job->next;
	}
	return (job);
}

t_job				*get_job_by_id(t_job *job, int id)
{
	while (job)
	{
		if (job->id == id)
			break ;
		job = job->next;
	}
	return (job);
}

t_job				*get_latest_job(t_job *job)
{
	while (job && job->next)
		job = job->next;
	return (job);
}

char				buildin_jobs_launch(t_shell *sh, char **argv, int mode)
{
	t_job		*job;

	job = NULL;
	if (ft_count_argv((void **)argv) == 0)
		job = get_latest_job(sh->job);
	else if (ft_count_argv((void **)argv) == 2 && is_valid_number(argv[1]))
	{
		if (!ft_strcmps(argv[0], "-i"))
			job = get_job_by_id(sh->job, ft_atoi(argv[1]));
		else if (!ft_strcmps(argv[0], "-p"))
			job = get_process_by_pid(sh->job, ft_atoi(argv[1]));
	}
	else
	{
		ft_printf("%s: wrong options\n", (mode == JOBS_FG) ? "fg" : "bg");
		return (STATUS_ERR);
	}
	if (!job)
		ft_printf("%s: no jobs\n", (mode == JOBS_FG) ? "fg" : "bg");
	else
		job_continue(job, mode);
	return (STATUS_OK);
}
