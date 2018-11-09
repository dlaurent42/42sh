/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_max_id.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:12:11 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 16:13:15 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			job_get_max_id(t_job *job)
{
	int			max;

	max = 0;
	while (job)
	{
		if (job->id > max)
			max = job->id;
		job = job->next;
	}
	return (max);
}
