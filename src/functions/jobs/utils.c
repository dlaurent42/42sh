/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:26:28 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/07 15:27:56 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			job_error(t_job *job, int pipe)
{
	if (pipe)
		ft_putendl_fd("sh: execution: pipe error", 2);
	else
		ft_putendl_fd("sh: execution: fork error", 2);
	job_delete(job);
}
