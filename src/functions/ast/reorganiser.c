/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/27 23:52:58 by dhojt            ###   ########.fr       */
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

static bool			token_is_redirect(t_token_tree *token)
{
	if (!token
			|| (token->type != 1
			&& token->type != 2
			&& token->type != 3))
		return (false);
	return (true);
}


static t_token_tree	*get_next_token(t_token_tree *token)
{
	t_token_tree	*next_token;

	next_token = token;
	if (next_token)	
		next_token = next_token->right;
	while (!token_is_redirect(next_token))
		next_token = next_token->right;
	return (next_token);
}

static void			insert_token_at_correct_place(
		t_token_tree *current_command,
		t_token_tree *current_token,
		t_token_tree *next_token)
{
	t_token_tree	*placeholder;

	//MOVE TO TOKEN PRIOR TO POINT OF INSERTION:
	while (current_command && get_next_token(current_command)
			&& get_next_token(current_command)->type <= current_token->type)
	{
		ft_printf("Moved past [%s]\n", *current_command->tokens);
		current_command = get_next_token(current_command);
	}

	//MOVE ONE AFTER THE ABOVE TOKEN:
	if (current_command
			&& current_command->right
			&& token_is_treatable(current_command->right))
		current_command = current_command->right;

	//MOVE TO POINT DIRECTLY BEFORE POINT OF INSERTION:
	while (current_command
			&& current_command->right
			&& token_is_treatable(current_command->right))
	{
		ft_printf("Move directly prior\n");
		current_command = current_command->right;
	}

	placeholder = current_command->right;

	//SET NEXT OF CURENT COMMAND TO CURRENT_TOKEN:
	current_command->right = current_token;

	//MOVE ONTO CURRENT_TOKEN:
	current_command = current_command->right;

	//MOVE PAST CURRENT_TOKEN's BASTARDS:
	while (current_command
			&& current_command->right
			&& token_is_treatable(current_command->right))
	{
		ft_printf("Move past bastards\n");
		current_command = current_command->right;
		sleep(1);
	}

	//SET CURRENT_TOTAL's BASTARD TO PLACEHOLDER.
	current_command->right = placeholder;

	//MOVE TO OLD->RIGHT POINTER TO CURRENT_TOKEN:
	while (current_command && current_command->right != current_token)
	{
		ft_printf("Move prior to old->right to current_token\n");
		current_command = current_command->right;
	}

	//SET OLD->RIGHT POINTER TO NEXT_TOKEN
	current_command->right = next_token;
}

static void			treat_current_command(t_token_tree *current_command)
{
	int				type;
	t_token_tree	*current_token;
	t_token_tree	*next_token;

	type = 0;
	current_token = current_command;
	while (current_token && current_token->type < 4)
	{
		ft_printf("    Current token[%s]\n", *current_token->tokens);
		if (type < current_token->type)
		{
			type = current_token->type;
			ft_printf("    Type:[%d]\n", type);
		}
		sleep(1);
		if (current_token->type < type)
		{
			ft_printf("    FIXING[%s]\n", *current_token->tokens);
			next_token = get_next_token(current_token);
			insert_token_at_correct_place(
					current_command, current_token, next_token);
			current_token = next_token;
		}
		sleep(1);
		current_token = get_next_token(current_token);
		if (current_token)//DELETE
			ft_printf("     Next token[%d][%s]\n", current_token->type, *current_token->tokens);
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

	//START
	current_command = *list;
	while (current_command)
	{
		ft_printf("END[%s]\n", *current_command->tokens);
		current_command = current_command->right;
	}
	ft_printf("\n----END REORGANISE----\n");
	return (1);
}
