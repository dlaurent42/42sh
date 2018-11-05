/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:01:39 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 15:57:51 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job		*job_new(void)
{
	t_job		*job;

	if (!(job = (t_job *)ft_memalloc(sizeof(t_job))))
		return (NULL);
	job->next = NULL;
	return (job);
}
