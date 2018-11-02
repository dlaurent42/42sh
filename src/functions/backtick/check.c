/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 20:26:30 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/31 20:29:49 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void			backtick_check(
					t_shell *sh, t_env *env, t_bin *bin, t_token_tree *tree)
{
	int		i;

	if (!tree)
		return ;
	i = -1;
	while (tree->tokens[++i])
		if (tree->t_type[i] == TOKEN_BACKQUOTE)
			tree->tokens[i] = backtick_prep(sh, env, bin, tree->tokens[i]);
}
