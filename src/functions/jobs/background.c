/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 19:07:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 19:10:19 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		put_job_in_background(t_job *job, int cont)
{
	if (cont)
		if (kill(-job->pgid, SIGCONT) < 0)
			ft_putendl_fd("kill (SIGCONT)", 2);
}
