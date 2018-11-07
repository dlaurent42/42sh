/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   foreground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:06:51 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/07 10:12:04 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		put_job_in_foreground(t_job *job, int cont)
{
	ft_printf("[foreground] Setting thread: job->pgid = %d\n", job->pgid);
	tcsetpgrp(STDIN_FILENO, job->pgid);
	if (cont)
	{
		tcsetattr(STDIN_FILENO, TCSADRAIN, &(job->tmodes));
		if (kill(-job->pgid, SIGCONT) < 0)
			ft_putendl_fd("kill (SIGCONT)", 2);
	}
	ft_printf("[foreground] Waiting for job\n");
	job_wait(job);
	ft_printf("[foreground] Waiting done\n");
	tcsetpgrp(STDIN_FILENO, g_sh->shell_pgid);
	tcgetattr(STDIN_FILENO, &(job->tmodes));
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(g_sh->termios));
}
