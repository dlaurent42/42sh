/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 18:05:58 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 18:09:48 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		job_message(t_job *job, char *status)
{
	ft_putnbr_fd(job->pgid, 2);
	ft_putstr_fd(" ", 2);
	ft_putendl_fd(status, 2);
}
