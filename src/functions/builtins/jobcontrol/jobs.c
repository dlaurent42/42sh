/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:37:37 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 14:57:51 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		buildin_jobs(t_shell *sh, char **argv)
{
	t_job		*job;

	if (ft_count_argv((void **)argv))
	{
		ft_putendl("jobs: bad option");
		return (STATUS_ERR);
	}
	job = sh->job;
	if (!job)
		ft_putendl("jobs: no jobs");
	else
		jobs_display(sh->job);
	return (STATUS_OK);
}
