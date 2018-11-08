/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:18:36 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 10:51:06 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	exec_main(t_shell *sh, t_token_tree *tree, int fd[2], int st)
{
	char res;

	dup2(fd[0], 0);
	close(fd[1]);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	res = execute_tree(sh, tree->right);
	dup2(st, 0);
	close(st);
	exit(res);
}

static char	exec_child(t_shell *sh, t_token_tree *tree, int fd[2], int st)
{
	char res;

	dup2(fd[1], 1);
	close(fd[0]);
	res = execute_tree(sh, tree->left);
	dup2(st, 1);
	close(st);
	exit(res);
}

static int	do_pipe(t_shell *sh, t_token_tree *tree, int fd[2], int std[2])
{
	pid_t	pid_left;
	pid_t	pid_right;
	int		stat[2];
	int		res;

	if ((pid_right = fork()) == -1)
		return (error_fork());
	else if (!pid_right)
		res = exec_main(sh, tree, fd, std[0]);
	if ((pid_left = fork()) == -1)
		return (error_fork());
	else if (!pid_left)
		res = exec_child(sh, tree, fd, std[1]);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid_right, &stat[0], 0);
	waitpid(pid_left, &stat[1], 0);
	if ((WIFEXITED(stat[0])))
		return (WEXITSTATUS(stat[0]));
	return (WIFEXITED(stat[1]) ? WEXITSTATUS(stat[0]) : STATUS_ERR);
}

/*
** std:
** 0 - in ; 1 - out
*/

char		execute_pipe(t_shell *sh, t_token_tree *tree)
{
	int		fd[2];
	int		std[2];
	int		ret;

	if (pipe(fd) == -1)
		return (error_pipe());
	std[0] = dup(0);
	std[1] = dup(1);
	sh->jc = 0;
	ret = do_pipe(sh, tree, fd, std);
	sh->jc = 1;
	return (ret);
}
