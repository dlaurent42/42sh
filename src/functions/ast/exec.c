/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:31:46 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/06 09:39:22 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** 7 - ; or &(jobs)
** 6 - ||
** 5 - &&
** 4 - |
** 3 - >&
** 2 - < or <<
** 1 - > or >>
** 0 - CMD
*/

int		execute_tree(t_shell *sh, t_token_tree *tree)
{
	int		ret;

	ret = 0;
	if (!tree)
		return (g_sh->exe);
	if (tree->type == 0)
		ret = sh_command_run_ast(sh, sh->exec->env,
			sh->exec->bin, tree);
	else if (tree->type == 1)
		ret = execute_right_redirection(sh, tree);
	else if (tree->type == 2)
		ret = execute_left_redirection(sh, tree);
	else if (tree->type == 3)
		ret = execute_fd_aggr(sh, tree);
	else if (tree->type == 4)
		ret = execute_pipe(sh, tree);
	else if (tree->type == 5 || tree->type == 6)
		ret = execute_conditions(sh, tree);
	else if (tree->type == 7)
		ret = execute_semicolon(sh, tree);
	if (tree->type == 0)
		g_sh->exe = ret;
	return (ret);
}
