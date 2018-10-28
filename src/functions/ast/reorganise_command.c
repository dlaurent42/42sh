/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/28 15:42:54 by dhojt            ###   ########.fr       */
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
	t_token_tree	*old_pointer_to_current_token;

	while (current_command && get_next_token(current_command)
			&& get_next_token(current_command)->type <= current_token->type)
		current_command = get_next_token(current_command);
	while (current_command
			&& current_command->right
			&& !token_is_redirect(current_command->right))
		current_command = current_command->right;
	placeholder = current_command->right;
	current_command->right = current_token;
	current_command = current_command->right;
	while (current_command
			&& current_command->right
			&& current_command->right->type == 0)
		current_command = current_command->right;
	current_command->right = placeholder;
	while (current_command && current_command->right
			&& current_command->right != current_token)
		current_command = current_command->right;
	old_pointer_to_current_token = current_command;
	current_command->right = next_token;
	return (old_pointer_to_current_token);
}

void				reorganise_command(t_token_tree *current_command)
{
	int				type;
	t_token_tree	*current_token;
	t_token_tree	*next_token;

	type = 0;
	current_token = current_command;
	while (current_token && current_token->type < 4)
	{
		type = (type < current_token->type) ? current_token->type : type;
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
