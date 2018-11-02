/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 19:19:08 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/02 14:12:02 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*backtick_process(t_shell *sh, t_token_tree *list)
{
	int fd[2];
	int len;
	int stdout;
	char buff[256];
	pid_t	pid;

	stdout = dup(1);
	pipe(fd);
	if ((pid = fork()) == -1)
		return (ft_strdups(""));
	else if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		(list) ? execute_tree(sh, list) : error_execution_tree();
		exit(STATUS_OK);
	}
	else
	{
		close(fd[1]);
		len = read(fd[0], buff, 255);
		buff[len] = '\0';
	}
	close(fd[0]);
	close(fd[1]);
	return (ft_strdups(buff));
}

char		*execute_backtick(t_shell *sh, t_lexer lexer)
{
	char			*ret;
	t_token_tree	*list;

	ret = NULL;
	list = build_list(lexer);
	reorganise_tokens(&list);
	list = build_token_tree(list);
	ret = backtick_process(sh, list);
	clean_tree(list);
	return (ret);
}
