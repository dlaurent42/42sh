/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 21:13:18 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 19:19:57 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		job_delete(t_job *job)
{
	t_process		*p;
	t_process		*tmp;

	if (!job)
		return ;
	p = job->first_process;
	while (p)
	{
		tmp = p;
		p = p->next;
		(tmp) ? free(tmp) : (0);
	}
	ft_strdel(&job->command);
	free(job);
}
