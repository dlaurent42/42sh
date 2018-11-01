/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganise_and_or.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 22:55:16 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/01 13:57:59 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			token_is_redirect(t_token_tree *token)
{
	if (!token
			|| (token->type != 5
			&& token->type != 6))
		return (false);
	return (true);
}

static t_token_tree	*get_next_token(t_token_tree *token)
{
	t_token_tree	*next_token;

	next_token = token;
	if (next_token)
		next_token = next_token->right;
	while (next_token && next_token->type != 5
		&& next_token->type != 6
		&& next_token->type != 7)
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
			&& current_command->right->type <= 4)
		current_command = current_command->right;
	current_command->right = placeholder;
	while (current_command && current_command->right
			&& current_command->right != current_token)
		current_command = current_command->right;
	old_pointer_to_current_token = current_command;
	current_command->right = next_token;
	return (old_pointer_to_current_token);
}

void				reorganise_and_or(t_token_tree *current_command)
{
	int				type;
	t_token_tree	*current_token;
	t_token_tree	*next_token;

	type = 0;
	current_token = current_command;
	while (current_token && current_token->type < 7)
	{
		type = (type < current_token->type) ? current_token->type : type;
		if (current_token->type < type)
		{
			next_token = get_next_token(current_token);
			current_token = insert_token_at_correct_place(
					current_command, current_token, next_token);
		}
		current_token = get_next_token(current_token);
	}
}
