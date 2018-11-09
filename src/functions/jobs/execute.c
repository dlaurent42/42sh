/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 10:52:11 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 10:23:06 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			sh_do_job(t_shell *sh, char **argv, t_env *env)
{
	int			ret;
	t_job		*job;
	t_process	*p;

	ret = STATUS_OK;
	job = job_new(sh->jc_muted, argv);
	job_add(sh, job);
	p = process_new();
	p->argv = argv;
	p->env = env;
	job->first_process = p;
	job_launch(job, (sh->jc_muted == 1) ? 0 : 1);
	if (env_search(env, "?"))
		ret = (ft_atoi(env_search(env, "?")));
	return (ret);
}
