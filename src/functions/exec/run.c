/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:57:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 22:31:29 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_command_exec(t_shell *sh, char **cmd, char **env)
{
	pid_t	pid;
	int		status;

	if ((sh->pid = fork()) == -1)
		return (-1);
	else if (sh->pid == 0)
	{
		execve(cmd[0], cmd, env);
	}
	else
	{
		pid = wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (-1);
}
