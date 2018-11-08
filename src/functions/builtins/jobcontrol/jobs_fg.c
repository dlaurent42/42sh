/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_fg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:41:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 22:02:05 by azaliaus         ###   ########.fr       */
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

	(void)argv;
	job = sh->job;
	if (!job)
		ft_putendl("fg: no current job");
	else
	{
		// Implement numbers ant etc;
		job_continue(sh->job, 1); // <- 1 - foreground | 0 - background
	}
	return (STATUS_OK);
	// return (jobs_finder(sh, argv, JOBS_FG));
}
