/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_token_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 13:39:38 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/24 13:54:20 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_token_tree		*get_top_tree(t_token_tree *list)
{
	t_token_tree		*tmp;
	int					max;

	tmp = list;
	max = 0;
	while (tmp)
	{
		if (tmp->type > max)
			max = tmp->type;
		tmp = tmp->right;
	}
	tmp = list;
	while (tmp)
	{
		if (tmp->type == max)
			return (tmp);
		tmp = tmp->right;
	}
	return (list);
}

static t_token_tree		*get_left_side(t_token_tree *list, t_token_tree *head)
{
	t_token_tree	*tmp;

	tmp = list;
	while (!(tmp == head || tmp->right == head))
		tmp = tmp->right;
	if (tmp == head)
		return (NULL);
	tmp->right = NULL;
	return (list);
}

t_token_tree			*build_token_tree(t_token_tree *list)
{
	t_token_tree		*head;
	t_token_tree		*left;
	t_token_tree		*right;

	if (!list)
		return (NULL);
	head = get_top_tree(list);
	right = head->right;
	left = get_left_side(list, head);
	head->left = build_token_tree(left);
	head->right = build_token_tree(right);
	return (head);
}
