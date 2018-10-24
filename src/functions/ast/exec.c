/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:31:46 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/24 16:06:03 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** 0 - CMD
** 6 - ;
** 5 - || or &&
** 4 - |
** 3 - >&
** 2 - < or <<
** 1 - > or >>
*/
int						execute_tree(t_shell *sh, t_env *env, t_bin *bin,
										t_token_tree *tree)
{
	int		ret;

	ret = 0;
	if (!tree)
		return (0);
	if (tree->type == 0)
		ret = sh_test_command_found(sh, env, bin, tree->tokens);
	// else if (tree->type == 1)
	// 	ret = execute_right_cursor(tree);
	// else if (tree->type == 2)
	// 	ret = execute_left_cursor(tree);
	// else if (tree->type == 3)
	// 	ret = execute_fd_aggr(tree);
	// else if (tree->type == 4)
	// 	ret = execute_pipe(tree);
	else if (tree->type == 5)
		ret = execute_conditions(sh, env, bin, tree);
	else if (tree->type == 6)
		ret = execute_semicolon(sh, env, bin, tree);
	return (ret);
}
