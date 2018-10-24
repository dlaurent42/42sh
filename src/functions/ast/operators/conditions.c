/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:05:05 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/24 16:48:46 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char					execute_conditions(t_shell *sh, t_token_tree *tree)
{
	char ret;

	ret = execute_tree(sh, tree->left);
	if ((!ft_strcmp(tree->tokens[0], "||") && ret != 0) ||
		(!ft_strcmp(tree->tokens[0], "&&") && ret == 0))
		ret = execute_tree(sh, tree->right);
	return (ret);
}
