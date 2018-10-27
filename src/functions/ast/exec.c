/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:31:46 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/28 01:15:22 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** 6 - ;
** 5 - || or &&
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
		return (0);
	if (tree->type == 0)
		ret = sh_command_run_ast(sh, sh->exec->env,
			sh->exec->bin, tree->tokens);
	else if (tree->type == 1)
		ret = execute_right_redirection(sh, tree);
	else if (tree->type == 2)
		ret = execute_left_redirection(sh, tree);
	else if (tree->type == 3)
		ret = execute_fd_aggr(sh, tree);
	else if (tree->type == 4)
		ret = execute_pipe(sh, tree);
	else if (tree->type == 5)
		ret = execute_conditions(sh, tree);
	else if (tree->type == 6)
		ret = execute_semicolon(sh, tree);
	if (tree->type == 0)
	{
		g_sh->exe = ret;
		ft_printf("g_sh->exe has been set to %d\n", ret);
	}
	ft_printf("execute tree is returning %d\n", ret);
	return (ret);
}
