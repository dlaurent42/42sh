/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 13:59:48 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 22:12:22 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			job_destroy_all(t_job *job)
{
	t_job		*tmp;

	while (job)
	{
		tmp = job;
		job = job->next;
		job_delete(tmp);
	}
}
