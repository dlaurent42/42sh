/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:40:44 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 17:45:30 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			job_is_completed(t_job *job)
{
	t_process	*p;

	p = job->first_process;
	while (p)
	{
		if (!p->completed)
			return (0);
		p = p->next;
	}
	return (1);
}
