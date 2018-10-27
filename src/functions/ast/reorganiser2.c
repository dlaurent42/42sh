/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 23:25:56 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 00:17:34 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			add_op(t_token_tree **lst, t_token_tree **tkns)
{
	if (in_range((*tkns)->type, 3, 6))
		add_tree_to_back(lst, copy_tree_node(*tkns));
	else
	{
		add_tree_to_back(lst, copy_tree_node(*tkns));
		// add_tree_to_back(lst, copy_tree_node((*tkns)->right));
	}
	return (1);
}

void		arrange_nodes_in_priority(t_token_tree **list)
{
	t_token_tree	*sorted;
	t_token_tree	*lst_sep;
	t_token_tree	*tokens;

	tokens = *list;
	sorted = NULL;
	while (tokens)
	{
		if (tokens->type == 0)
		{
			add_tree_to_back(&sorted, copy_tree_node(tokens));
			lst_sep = get_tree_last_node(sorted);
			skip_and_sort(&tokens, &lst_sep);
			if (tokens && in_range(tokens->type, 4, 6) && add_op(&sorted, &tokens))
				continue ;
			if (!tokens)
				break ;
		}
		add_op(&sorted, &tokens);
		if (!tokens)
			break ;
		skip_and_sort(&tokens, &lst_sep);
		(tokens && in_range(tokens->type, 4, 6)) ? add_op(&sorted, &tokens) : (0);
	}

	while (sorted)
	{
		printf("Node: %s\n", sorted->tokens[0]);
		sorted = sorted->right;
	}
	// re_assign_to_tkns(shell, sorted);
}
