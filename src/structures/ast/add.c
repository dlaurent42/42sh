/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 21:38:48 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 21:56:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_tree_node(t_token_tree **head, t_token_tree **last,
						t_token_tree *new)
{
	if (*head == NULL)
		*head = new;
	else
		(*last)->right = new;
	*last = new;
}

int		add_tree_to_back(t_token_tree **head, t_token_tree *new)
{
	t_token_tree	*cpy;

	cpy = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (cpy->right != NULL)
			cpy = cpy->right;
		cpy->right = new;
	}
	return (1);
}
