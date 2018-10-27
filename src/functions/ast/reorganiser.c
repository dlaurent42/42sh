/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 18:11:20 by dhojt            ###   ########.fr       */
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
	int				id;

	id = 0;
	while (list)
	{
		list->id = id++;
		list = list->right;
	}
}

int					reorganise_tokens(t_token_tree **list)
{
	ft_printf("\n----START REORGANISE----\n\n");
	t_token_tree	*current_command;

	current_command = *list;
	assign_token_ids(current_command);
	while (current_command)
	{
		ft_printf("Current command [%s]\n", *current_command->tokens);
		treat_current_command(current_command);
		while (current_command && token_is_treatable(current_command))
			current_command = current_command->right;
		while (current_command && !token_is_treatable(current_command))
			current_command = current_command->right;
	}
	ft_printf("\n----END REORGANISE----\n");
	return (1);
}
