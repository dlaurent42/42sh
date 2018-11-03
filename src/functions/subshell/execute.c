/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 17:56:26 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/03 20:19:16 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int				main(int argc, char **argv, char **environ);

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

char			execute_subshell(
				t_shell *sh, t_env *env, t_token_tree *tree)
{
	pid_t		pid;
	int			status;
	char		**arr;

	if (!(arr = build_argv(tree->tokens[0], sh)))
		return (error_subshell());
	if ((pid = fork()) == -1)
		return (error_subshell());
	else if (pid == 0)
		exit(main(2, arr, env->environment));
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
