/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 19:19:08 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/10 16:12:20 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		*backtick_process(t_shell *sh, t_token_tree *list)
{
	int		fd[2];
	int		stdout;
	pid_t	pid;
	int		status;
	char	*ret;

	stdout = dup(1);
	ret = NULL;
	if ((pipe(fd) == -1) || (pid = fork()) == -1)
		return (ft_strdups(""));
	else if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[1]);
		write(1, " ", 1);
		(list) ? execute_tree(sh, list) : error_execution_tree();
		exit(sh->exe);
	}
	else if ((int)(pid = wait(&status)))
		ret = backtick_capture(fd[0]);
	dup2(fd[1], stdout);
	close(stdout);
	close(fd[0]);
	close(fd[1]);
	return (ret);
}

char			*execute_backtick(t_shell *sh, t_lexer lexer)
{
	char			*ret;
	char			*tmp;
	t_token_tree	*list;

	ret = NULL;
	list = build_list(lexer);
	reorganise_tokens(&list);
	list = build_token_tree(list);
	ret = backtick_process(sh, list);
	if (ret)
	{
		tmp = ret;
		ret = ft_strdups(ret + 1);
		ft_strdel(&tmp);
	}
	clean_tree(list);
	return (ret);
}
