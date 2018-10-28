/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:50:01 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/24 17:22:50 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		execute_semicolon(t_shell *sh, t_token_tree *tree)
{
	int		ret;

	ret = 0;
	if (!tree)
		return (0);
	ret = execute_tree(sh, tree->left);
	ret = execute_tree(sh, tree->right);
	return (ret);
}
