/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_by_id.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:14:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 16:15:48 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job			*job_get_by_id(t_job *job, int id)
{
	while (job)
	{
		if (job->id == id)
			return (job);
		job = job->next;
	}
	return (NULL);
}
