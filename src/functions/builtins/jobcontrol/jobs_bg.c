/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_bg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:38:34 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 21:58:04 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** For Dav:
** fg w/o number should make affect the last process of sh->job list.
** w/ number should call job with that job_id. (also ID needs to be appended.)
*/
char		buildin_jobs_bg(t_shell *sh, char **argv)
{
	t_job		*job;

	(void)argv;
	job = sh->job;
	if (!job)
		ft_putendl("bg: no current job");
	else
	{
		// Implement numbers ant etc;
		job_continue(sh->job, 0);
	}
	return (STATUS_OK);
	// return (jobs_finder(sh, argv, JOBS_BG));
}
