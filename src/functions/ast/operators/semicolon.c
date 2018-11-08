/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:50:01 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/08 15:10:50 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		execute_semicolon(t_shell *sh, t_token_tree *tree)
{
	int		ret;

	ret = 0;
	if (!tree)
		return (0);
	(ft_strcmp(tree->tokens[0], "&") == 0) ? sh->jc_muted = 1 : (0);
	ret = execute_tree(sh, tree->left);
	sh->jc_muted = 0;
	ret = execute_tree(sh, tree->right);
	return (ret);
}
