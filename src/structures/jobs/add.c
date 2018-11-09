/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:21:13 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 16:01:30 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	job_get_id(t_job *job)
{
	int		ret;
	int		curr;
	t_job	*cpy;
	t_job	*loop;

	ret = 1;
	cpy = job;
	while (job)
	{
		curr = job->id;
		loop = cpy;
		while (loop)
		{
			if (curr + 1 == loop->id)
				break ;
			loop = loop->next;
		}
		if (loop == NULL)
			return (curr + 1);
		job = job->next;
		ret++;
	}
	return (ret);
}

static void	job_decrese_all_ranks(t_job *job)
{
	while (job)
	{
		job->rank--;
		job = job->next;
	}
}

void		job_add(t_shell *sh, t_job *new)
{
	t_job		*curr;
	int			get_id;

	curr = sh->job;
	get_id = job_get_id(sh->job);
	if (!curr)
		sh->job = new;
	else
	{
		job_decrese_all_ranks(sh->job);
		new->id = get_id;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
}
