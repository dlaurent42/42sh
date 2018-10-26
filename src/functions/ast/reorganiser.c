/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 10:43:47 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/26 11:27:59 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int		in_range(int i, int begin, int end)
{
	return ((i <= end && i >= begin));
}

static void		move_tokens(t_token_tree *list, t_token_tree **begin,
							t_token_tree **node1, t_token_tree **node2)
{
	if (!begin)
		return ;
	*begin = list;
	*node1 = (*begin)->right;
	if (node2)
		*node2 = (*node1 ? (*node1)->right : NULL);
}

static void		reorganise_tokens_do(t_token_tree **list)
{
	t_token_tree		*begin;
	t_token_tree		*node1;
	t_token_tree		*node2;

	move_tokens(*list, &begin, &node1, &node2);
	while (*list && node2)
	{
		while (node2 && !in_range(node1->type, 4, 6))
		{
			if ((node2 && in_range(node1->type, 1, 3) && node2->size >= 2) ||
				(node1->type == 3 && node2->type == 0))
			{
				// token_bring_to_front(&begin, &node2);
				reorganise_tokens_helper(list);
				return ;
			}
			node1 = node1->right;
			node2 = node2->right;
		}
		if (in_range(node1->type, 4, 6))
			move_tokens(node1->right, &begin, &node1, &node2);
	}
}

void			reorganise_tokens(t_token_tree **list)
{
	reorganise_tokens_do(list);
}
