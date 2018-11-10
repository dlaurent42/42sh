/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 10:59:48 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/10 16:08:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*get_fd(char *token)
{
	int			i;
	char		*ret;

	ret = NULL;
	i = 0;
	while (token[i] && token[i] != '<')
		i++;
	if (i > 0)
		ret = ft_strndup(token, i);
	return (ret);
}

static void	execute_heredoc_main(
			t_shell *sh, t_token_tree *tree, int stdin, int fd[2])
{
	int		status;
	char	*front;
	int		fd_targ;

	front = get_fd(tree->tokens[0]);
	fd_targ = (front ? ft_atoi(front) : 0);
	ft_strdel(&front);
	dup2(fd[0], fd_targ);
	close(fd[1]);
	wait(&status);
	execute_tree(sh, tree->left);
	dup2(stdin, fd_targ);
	close(stdin);
	exit(0);
}

static void	execute_heredoc_child(
			t_shell *sh, int count, int stdout, int fd[2])
{
	char		*str;

	str = NULL;
	dup2(fd[1], 1);
	close(fd[0]);
	while (count--)
	{
		ft_strdel(&str);
		str = sh_heredoc_get_next(sh);
	}
	ft_putstr_fd(str ? str : "", 1);
	dup2(stdout, 1);
	close(stdout);
	exit(0);
}

static char	do_heredoc(
			t_shell *sh, t_token_tree *tree, int std[2], int count)
{
	int		fd[2];
	int		status;
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fd) == -1)
		return (error_pipe());
	if ((pid_left = fork()) == -1)
		return (error_fork());
	else if (!pid_left)
		execute_heredoc_main(sh, tree, std[0], fd);
	if ((pid_right = fork()) == -1)
		return (error_fork());
	else if (!pid_right)
		execute_heredoc_child(sh, count, std[1], fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_right, &status, 0);
	waitpid(pid_left, &status, 0);
	return (0);
}

char		left_heredoc(t_shell *sh, t_token_tree *tree, int count)
{
	int		std[2];

	std[0] = dup(0);
	std[0] = dup(1);
	return (do_heredoc(sh, tree, std, count));
}
