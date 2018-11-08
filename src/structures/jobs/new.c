/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:01:39 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 11:37:25 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job		*job_new(void)
{
	t_job		*job;

	if (!(job = (t_job *)ft_memalloc(sizeof(t_job))))
		return (NULL);
	job->fd[0] = STDIN_FILENO;
	job->fd[1] = STDOUT_FILENO;
	job->fd[2] = STDERR_FILENO;
	job->notifications = 0;
	job->next = NULL;
	return (job);
}
