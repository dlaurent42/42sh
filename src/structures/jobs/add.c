/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:21:13 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/06 13:35:30 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		job_add(t_shell *sh, t_job *new)
{
	t_job		*curr;

	curr = sh->job;
	if (!curr)
		sh->job = new;
	else
	{
		sh->job = new;
		new->next = curr;
	}
}
