/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/10 13:54:32 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/10 15:16:52 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		redir_load_job(t_job *job, t_redir *redir)
{
	if (!job || !redir)
		return ;
	while (redir)
	{
		job->fd[redir->front] = redir->back;
		redir = redir->next;
	}
}
