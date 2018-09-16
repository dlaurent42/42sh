/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fetch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:22:30 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/16 15:56:17 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_handler(int *pipe_fd, char *path, char **argv, char **envp)
{
	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], 1) == -1)
		return ;
	if (execve(path, argv, envp) == -1)
		return ;
	return ;
}

static char	*parent_handler(int *pipe_fd)
{
	int		ret;
	char	buffer[1024];
	char	*command_output;

	close(pipe_fd[1]);
	command_output = NULL;
	while ((ret = read(pipe_fd[0], buffer, 1023)) != 0)
	{
		buffer[ret] = 0;
		command_output = ft_strjoinf(command_output, buffer, 1);
	}
	return (command_output);
}

char		*bin_execute_fetch(t_shell *shell, char *path, char **args)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	*command_output;

	command_output = NULL;
	if (pipe(pipe_fd) == -1)
		return (NULL);
	if ((pid = fork()) == -1)
		return (NULL);
	else if (pid == 0)
		child_handler(pipe_fd, path, args, shell->env->environment);
	else
		command_output = parent_handler(pipe_fd);
	return (command_output);
}
