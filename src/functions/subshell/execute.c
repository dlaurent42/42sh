/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 17:56:26 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/10 11:25:20 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		subshell_main(int argc, char **argv, char **environ)
{
	int			status;
	t_shell		*sh;

	sh = NULL;
	sh = sh_new(argc, argv, environ);
	(argc == 1) ? sh_welcome() : 0;
	signal_catching();
	status = (argc == 1)
		? sh_read(sh)
		: sh_subshell(sh, argv + 1);
	sh_delete(sh);
	return (status);
}

static char		**build_argv(char *token, t_shell *sh)
{
	char		**arr;

	if (!(arr = (char **)ft_memalloc(sizeof(char *) * 3)))
		return (NULL);
	arr[0] = ft_strdups(env_search(sh->env, "0"));
	arr[1] = ft_strdups(token);
	arr[2] = NULL;
	return (arr);
}

char			execute_subshell_env(t_env *env, char **arr)
{
	pid_t		pid;
	int			status;

	if (!arr || lexer_is_empty(arr[0]))
		return (STATUS_OK);
	if ((pid = fork()) == -1)
		return (error_subshell());
	else if (pid == 0)
		exit(subshell_main(2, arr, env->environment));
	else
	{
		pid = wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (STATUS_OK);
}

char			execute_subshell(t_shell *sh, t_env *env, t_token_tree *tree)
{
	pid_t		pid;
	int			status;
	char		**arr;

	if (!tree->tokens[0] || lexer_is_empty(tree->tokens[0]))
		return (STATUS_OK);
	if (!(arr = build_argv(tree->tokens[0], sh)))
		return (error_subshell());
	if ((pid = fork()) == -1)
		return (error_subshell());
	else if (pid == 0)
		exit(subshell_main(2, arr, env->environment));
	else
	{
		pid = wait(&status);
		ft_deltab(arr);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	ft_deltab(arr);
	return (STATUS_OK);
}
