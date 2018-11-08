/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:52:11 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 14:06:52 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			sh_do_job(t_shell *sh, char **argv, t_env *env)
{
	int			ret;
	t_job		*job;
	t_process	*p;

	job = job_new();
	job_add(sh, job);
	p = process_new();
	p->argv = argv;
	p->env = env;
	job->first_process = p;
	job_launch(job, 1);
	// Replace it with nanosleep
	usleep(2000);
	ret = STATUS_OK;
	return (ret);
}
