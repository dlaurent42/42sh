/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:50:01 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/24 15:51:54 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		execute_semicolon(t_shell *sh, t_env *env, t_bin *bin,
										t_token_tree *tree)
{
	int		ret;

	ret = 0;
	if (!tree)
		ret = 0;
	else
	{
		ret = execute_tree(sh, env, bin, tree->left);
		ret = execute_tree(sh, env, bin, tree->right);
	}
	return (ret);
}
