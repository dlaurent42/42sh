/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 13:31:06 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// 						t_token_tree **node1, t_token_tree **node2)
// {
// 	if (!list)
// 		return ;
// 	*begin = list;
// 	*node1 = (*begin)->right;
// 	if (node2)
// 		*node2 = (*node1) ? (*node1)->right : NULL;
// }
//
// static int	reogranisation(t_token_tree **list)
// {
// 	t_token_tree	*begin;
// 	t_token_tree	*node1;
// 	t_token_tree	*node2;
//
// 	move_tokens(*list, &begin, &node1, &node2);
// 	while (begin && node2)
// 	{
// 		while (node2 && !in_range(node1->type, 4, 6))
// 		{
// 			if ((node2 && in_range(node1->type, 1, 3) && node2->size >= 2) ||
// 				(node1->type == 3 && node2->type == 0))
// 			{
// 				printf("Bringing tokens to front!\n");
// 				// tokens_bring_front(&begin, &node2);
// 				reogranisation(list);
// 				return (1);
// 			}
// 			node1 = node1->right;
// 			node2 = node2->right;
// 		}
// 		if (in_range(node1->type, 4, 6))
// 			move_tokens(node1->right, &begin, &node1, &node2);
// 	}
// 	return (1);
// }

int			reorganise_tokens(t_token_tree **list)
{
	(void)list;
	// reogranisation(list);
	// arrange_nodes_in_priority(list);
	return (1);
}
