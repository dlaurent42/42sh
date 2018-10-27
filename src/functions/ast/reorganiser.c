/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 20:14:21 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			token_is_treatable(t_token_tree *token)
{
	if (!token
			|| token->type == 4
			|| token->type == 5
			|| token->type == 6)
		return (false);
	return (true);
}

static void			insert_token_at_correct_place(
		t_token_tree *current_command,
		t_token_tree *current_token,
		t_token_tree *next_token)
{
	if (current_token || current_command || next_token)
		;
}

static t_token_tree	*get_next_token(t_token_tree *current_token)
{
	t_token_tree	*next_token;

	next_token = current_token;
	while (next_token && token_is_treatable(next_token))
		next_token = next_token->right;
	return (next_token);
}
	


static void			treat_current_command(t_token_tree *current_command)
{
	int				type;
	t_token_tree	*current_token;
	t_token_tree	*next_token;

	type = 0;
	current_token = current_command;
	while (token_is_treatable(current_token))
	{
		type = (type < current_token->type) ? current_token->type : type;
		if (current_token->type < type)
		{
			next_token = get_next_token(current_token);
			insert_token_at_correct_place(
					current_command, current_token, next_token);
			current_token = next_token;
		}
		current_token = (current_token) ? current_token->right : current_token;
	}
}

static void			move_to_next_command(t_token_tree **current_command)
{
	while (*current_command && token_is_treatable(*current_command))
		*current_command = (*current_command)->right;
	while (*current_command && !token_is_treatable(*current_command))
		*current_command = (*current_command)->right;
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
	t_token_tree	*current_command;

	ft_printf("\n----START REORGANISE----\n\n");
	current_command = *list;
	assign_token_ids(current_command);
	while (current_command)
	{
		ft_printf("Current command [%s]\n", *current_command->tokens);
		treat_current_command(current_command);
		move_to_next_command(&current_command);
	}
	ft_printf("\n----END REORGANISE----\n");
	return (1);
}
