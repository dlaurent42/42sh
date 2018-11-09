/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_fg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:41:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 09:26:06 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** For Dav:
** fg w/o number should make affect the last process of sh->job list.
** w/ number should call job with that job_id. (also ID needs to be appended.)
*/
char		buildin_jobs_fg(t_shell *sh, char **argv)
{
	t_job		*job;

	job = sh->job;
	if (!job)
		ft_putendl("fg: no current job");
	else
	{
		if (!ft_count_argv((void **)argv))
		{
			while (job->next)
				job = job->next;
			job_continue(job, 1);
		}
		else if (ft_count_argv((void **)argv) == 1)
		{
			// Dav: do stuff
			// Return proper job and run this
			job_continue(job, 1); // <- 1 - foreground | 0 - background
		}
		else
		{
			ft_putendl("fg: too much arguments");
			return (STATUS_OK);
		}
	}
	return (STATUS_OK);
	// return (jobs_finder(sh, argv, JOBS_FG));
}
