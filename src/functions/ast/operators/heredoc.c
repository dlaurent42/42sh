/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 10:59:48 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/26 10:22:00 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	execute_heredoc_main(t_shell *sh, t_token_tree *tree, int stdin,
									int fd[2])
{
	int		status;

	dup2(fd[0], 0);
	close(fd[1]);
	wait(&status);
	execute_tree(sh, tree->left);
	dup2(stdin, 0);
	close(stdin);
	exit(0);
}

static void	execute_heredoc_child(t_shell *sh, t_token_tree *tree, int stdout,
									int fd[2])
{
	dup2(fd[1], 1);
	close(fd[0]);
	(void)sh;
	(void)tree;
	// Get most right heredoc in tree.
	// TODO: do it after merge
	dup2(stdout, 1);
	close(stdout);
	exit(0);
}

static char	do_heredoc(t_shell *sh, t_token_tree *tree, int stdin, int stdout)
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
		execute_heredoc_main(sh, tree, stdin, fd);
	if ((pid_right = fork()) == -1)
		return (error_fork());
	else if (!pid_right)
		execute_heredoc_child(sh, tree, stdout, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_right, &status, 0);
	waitpid(pid_left, &status, 0);
	return (0);
}

char		left_heredoc(t_shell *sh, t_token_tree *tree)
{
	int		stdin;
	int		stdout;

	stdin = dup(0);
	stdout = dup(1);
	return (do_heredoc(sh, tree, stdin, stdout));
}
