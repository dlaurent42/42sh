/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 10:59:48 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/25 12:33:40 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	{
		dup2(fd[0], 0);
		close(fd[1]);
		wait(&status);
		execute_tree(sh, tree->left);
		dup2(stdin, 0);
		close(stdin);
		exit(0);
	}
}

char		left_heredoc(t_shell *sh, t_token_tree *tree)
{
	int		stdin;
	int		stdout;

	stdin = dup(0);
	stdout = dup(1);
	return (do_heredoc(sh, tree, stdin, stdout));
}
