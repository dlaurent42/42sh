/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_execve_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:18:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/15 19:27:14 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int	main(int argc, char *argv[], char *env[])
{
	pid_t	pid;
	int		pipe_fd[2];
	char	buffer[1024];
	int		ret;

	if (pipe(pipe_fd) == -1)
		return (1);
	if ((pid = fork()) == -1)
		return (1);
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], 1) == -1)
			return (1);
		else if (execve(argv[1], argv + 1, env) == -1)
			return (1);
		return (1);
	}
	else
	{
		close(pipe_fd[1]);
		while ((ret = read(pipe_fd[0], buffer, 1023)) != 0)
		{
			printf("%d\n", ret);
			buffer[ret] = 0;
			//printf("%s\n", buffer);
		}
	}
	return (1);
}
