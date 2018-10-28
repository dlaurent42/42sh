/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/28 14:58:00 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	while (next_token && next_token->type == 0)
		next_token = next_token->right;
	return (next_token);
}

static t_token_tree	*insert_token_at_correct_place(
		t_token_tree *current_command,
		t_token_tree *current_token,
		t_token_tree *next_token)
{
	t_token_tree	*placeholder;
	t_token_tree	*old_pointer_to_current_token;;

	//MOVE TO TOKEN PRIOR TO POINT OF INSERTION:
	while (current_command && get_next_token(current_command)
			&& get_next_token(current_command)->type <= current_token->type)
		current_command = get_next_token(current_command);
	//MOVE TO POINT DIRECTLY BEFORE POINT OF INSERTION:
	while (current_command
			&& current_command->right
			&& !token_is_redirect(current_command->right))
		current_command = current_command->right;
	//PLACE HOLDER IS POINT AFTER INSERTION
	placeholder = current_command->right;
	//SET NEXT OF CURENT COMMAND TO CURRENT_TOKEN:
	current_command->right = current_token;
	//MOVE ONTO CURRENT_TOKEN:
	current_command = current_command->right;
	//MOVE PAST CURRENT_TOKEN's BASTARDS:
	while (current_command
			&& current_command->right
			&& current_command->right->type == 0)
		current_command = current_command->right;
	//SET CURRENT_TOTAL's BASTARD TO PLACEHOLDER.
	current_command->right = placeholder;
	//MOVE TO OLD->RIGHT POINTER TO CURRENT_TOKEN:
	while (current_command && current_command->right
			&& current_command->right != current_token)
		current_command = current_command->right;
	//SET OLD->RIGHT POINTER TO NEXT_TOKEN
	old_pointer_to_current_token = current_command;
	current_command->right = next_token;
	return (old_pointer_to_current_token);
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
		if (type < current_token->type)
			type = current_token->type;
		if (current_token->type == 3 && current_token->right
				&& current_token->right->type == 0)
		{
			current_token = current_token->right;
			next_token = get_next_token(current_token);
			current_token = insert_token_at_correct_place(
					current_command, current_token, next_token);
		}
		else if (current_token->type < type)
		{
			next_token = get_next_token(current_token);
			current_token = insert_token_at_correct_place(
					current_command, current_token, next_token);
		}
		current_token = get_next_token(current_token);
	}
}

static bool			token_is_boundry(t_token_tree *token)
{
	if (!token
			|| (token->type != 4
			&& token->type != 5
			&& token->type != 6))
		return (false);
	return (true);
}

static void			move_to_next_command(t_token_tree **current_command)
{
	while (*current_command && !token_is_boundry(*current_command))
		*current_command = (*current_command)->right;
	while (*current_command && token_is_boundry(*current_command))
		*current_command = (*current_command)->right;
}

int					reorganise_tokens(t_token_tree **list)
{
	t_token_tree	*current_command;

	current_command = *list;
	//////BEFORE
	//START
	current_command = *list;
	while (current_command)
	{
		ft_printf("END[%s]\n", *current_command->tokens);
		current_command = current_command->right;
	}
	current_command = *list;
	//END
	while (current_command)
	{
		ft_printf("treat command[%s]\n", *current_command->tokens);

		treat_current_command(current_command);

		ft_printf("end command[%s]\n", *current_command->tokens);

		move_to_next_command(&current_command);
	}

	ft_printf("\n----END REORGANISE----\n");
	//////AFTER
	//START
	current_command = *list;
	while (current_command)
	{
		ft_printf("END[%s]\n", *current_command->tokens);
		current_command = current_command->right;
	}
	//END
	return (1);
}
