/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_fg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:41:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 17:21:31 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		job_continue(sh->job, 1);
	}
	return (STATUS_OK);
	// return (jobs_finder(sh, argv, JOBS_FG));
}
