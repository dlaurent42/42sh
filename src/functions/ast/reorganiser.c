/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 17:57:07 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	return (1);
}
