/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 21:38:48 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/24 11:31:57 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_tree_node(t_token_tree **head, t_token_tree **last,
						t_token_tree *new)
{
	if (*head == NULL)
		*head = new;
	else
		(*last)->next = new;
	*last = new;
}

void add_tree_to_back(t_token_tree **head, t_token_tree *new)
{
	t_token_tree	*cpy;

	cpy = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (cpy->next != NULL)
			cpy = cpy->next;
		cpy->next = new;
	}
}
