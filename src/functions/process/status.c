/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:15:58 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 15:01:45 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <errno.h>

/*
**	When errno == ECHILD - there is no process to get.
*/

static int	process_status_err(pid_t pid)
{
	if (pid == 0 || errno == ECHILD)
		return (-1);
	ft_putendl_fd("waitpid error", 2);
	return (-1);
}

static int	process_found(t_job *job, t_process *p, int status)
{
	char		*st;

	st = NULL;
	p->status = status;
	if (WIFSTOPPED(status))
		p->stopped = 1;
	else
	{
		p->completed = 1;
		st = ft_itoa(WEXITSTATUS(status));
		if (env_search(g_sh->env, "?")
		|| g_sh->env->count + 1 < g_sh->env->size)
			env_insert_protected(g_sh, g_sh->env, "?", st);
		if (WIFSIGNALED(status))
			job->notifications = 0;
	}
	ft_strdel(&st);
	return (0);
}

int			process_status(pid_t pid, int status)
{
	t_job		*job;
	t_process	*p;

	if (pid <= 0)
		return (process_status_err(pid));
	job = g_sh->job;
	while (job)
	{
		p = job->first_process;
		while (p)
		{
			if (p->pid == pid)
				return (process_found(job, p, status));
			p = p->next;
		}
		job = job->next;
	}
	ft_putendl_fd("No child process", 2);
	return (-1);
}
