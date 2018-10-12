/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:57:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 20:54:40 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_command_exec_close_pipes(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
}

char		sh_command_exec(t_shell *sh, char **cmd, char **env)
{
	pid_t	pid;
	int		status;
	int		pipes[2][2];

	pipe(pipes[1]);
	pipe(pipes[0]);
	if ((sh->pid = fork()) == -1)
		return (-1);
	else if (sh->pid == 0)
	{
		sh_command_exec_close_pipes(pipes[0]);
		sh_command_exec_close_pipes(pipes[1]);
		execve(cmd[0], cmd, env);
	}
	else
	{
		sh_command_exec_close_pipes(pipes[0]);
		pid = wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (-1);
}
