/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 19:19:08 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/31 21:18:39 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*execute_backtick(
				t_shell *sh, t_env *env, t_bin *bin, t_lexer lexer)
{
	char			*ret;
	t_token_tree	*list;

	ret = NULL;
	list = build_list(lexer);
	reorganise_tokens(&list);
	t_exec *exec = sh->exec;
	if (!(sh->exec = sh_init_exec(env, bin)))
	{
		clean_tree(list);
		return (ft_strdups(""));
	}
	list = build_token_tree(list);

	int fd[2];
	int len;
	int stdout;
	char buff[256];
	pid_t	pid;

	stdout = dup(1);
	pipe(fd);


	if ((pid = fork()) == 0)
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
		ret = ft_strdups(buff);
	}
	close(fd[0]);
	close(fd[1]);
	clean_tree(list);
	sh_destroy_exec(&(sh->exec));
	sh->exec = exec;
	return (ret);
}
