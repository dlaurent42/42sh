/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:54:26 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 17:51:53 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		process_launch(t_process *p, pid_t pgid, int fd[3], int foreground)
{
	pid_t		pid;

	if (1) // shell active ; not sure is needed
	{
		pid = getpid();
		(pid == 0) ? pgid = pid : (0);
		setpgid(pid, pgid);
		if (foreground)
			tcsetpgrp(STDIN_FILENO, pgid); // from header. not sure what to do;
		// signal reset -> not sure if needed
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);
		signal(SIGTTIN, SIG_DFL);
		signal(SIGTTOU, SIG_DFL);
		signal(SIGCHLD, SIG_DFL);
	}
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
	ft_printf("Launching process: %s\n", p->argv[0]);
	execve(p->argv[0], p->argv, p->env->environment);
	ft_putendl_fd("Error on execve(process/launch.c)", 2);
	exit(1);
}
