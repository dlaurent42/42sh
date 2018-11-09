/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_launch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 12:10:04 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/09 12:12:19 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char				*jobs_launch(t_shell *sh, char **argv, int mode)
{
	t_job		*job;

	job = sh->job;
	if (!job)
		ft_putendl("bg: no current job");
	else
	{
		if (!ft_count_argv((void **)argv))
		{
			while (job->next)
				job = job->next;
			job_continue(job, 0); // <- 1 - foreground | 0 - background
		}
		else if (ft_count_argv((void **)argv) == 1)
		{
			// Dav: do stuff
			// Return proper job and run this
			job_continue(job, 0); // <- 1 - foreground | 0 - background
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
