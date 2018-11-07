/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:05:58 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/07 16:14:47 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		job_message_suspended(t_job *job)
{
	t_process		*p;

	p = job->first_process;
	ft_putstr_fd("[JOB_ID] ", 2);
	while (p)
	{
		ft_putnbr_fd(p->pid, 2);
		ft_putstr_fd(" ", 2);
		if (p->completed && !p->stopped)
			ft_putstr_fd("done\n", 2);
		else if (p->stopped)
			ft_putstr_fd("suspended\n", 2);
		p = p->next;
	}
}

void		job_message(t_job *job, char *status)
{
	t_process		*p;

	p = job->first_process;
	ft_putstr_fd("[JOB_ID] ", 2);
	while (p)
	{
		ft_putnbr_fd(p->pid, 2);
		ft_putstr_fd(" ", 2);
		p = p->next;
	}
	ft_putendl_fd(status, 2);
}
