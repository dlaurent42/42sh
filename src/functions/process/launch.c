/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:54:26 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/07 15:23:33 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		process_launch(t_process *p, pid_t pgid, int fd[3], int foreground)
{
	pid_t		pid;

	pid = getpid();
	(pgid == 0) ? pgid = pid : (0);
	setpgid(pid, pgid);
	(foreground) ? tcsetpgrp(STDIN_FILENO, pgid) : (0);
	signal_default();
	if (fd[0] != STDIN_FILENO)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	if (fd[1] != STDOUT_FILENO)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (fd[2] != STDERR_FILENO)
	{
		dup2(fd[2], STDERR_FILENO);
		close(fd[2]);
	}
	execve(p->argv[0], p->argv, p->env->environment);
	ft_putendl_fd("Error on executing process", 2);
	exit(1);
}
