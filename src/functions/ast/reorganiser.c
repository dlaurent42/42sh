/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 17:55:45 by dhojt            ###   ########.fr       */
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

//static bool			tokens_are_ordered(t_token_tree *list)
//{
//	return (true);
//}

static bool			token_is_treatable(t_token_tree *current_token)
{
	if (!current_token
			|| current_token->type == 4
			|| current_token->type == 5
			|| current_token->type == 6)
		return (false);
	return (true);
}

static void			treat_current_command(t_token_tree *head)
{
	t_token_tree	*current_token;

	current_token = head;
	while (token_is_treatable(current_token))
	{
		current_token = current_token->right;
	}
}

static void			assign_token_ids(t_token_tree *list)
{
	int				i;

	i = 0;
	while (list)
	{
		list->id = i++;
		list = list->right;
	}
}

int					reorganise_tokens(t_token_tree **list)
{
	t_token_tree	*current_command;

	current_command = *list;
	assign_token_ids(*list);
	while (current_command && !token_is_treatable(current_command))
	{
		treat_current_command(current_command);
		while (current_command && !token_is_treatable(current_command))
		{
			current_command = current_command->right;
		}	
	}
	// reogranisation(list);
	// arrange_nodes_in_priority(list);
	return (1);
}
