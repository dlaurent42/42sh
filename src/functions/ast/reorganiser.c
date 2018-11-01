/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/01 11:55:01 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			move_past_next_semicolon(t_token_tree **current_command)
{
	while (*current_command && (*current_command)->type != 7)
		*current_command = (*current_command)->right;
	while (*current_command && (*current_command)->type == 7)
		*current_command = (*current_command)->right;
}

static bool			token_is_boundry(t_token_tree *token)
{
	if (!token
			|| (token->type != 4
				&& token->type != 5
				&& token->type != 6
				&& token->type != 7))
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
	while (current_command)
	{
		reorganise_command(current_command);
		if (!(squash_type_zero(current_command)))
			return (STATUS_ERR);
		move_to_next_command(&current_command);
	}
	current_command = *list;
	while (current_command)
	{
		reorganise_and_or(current_command);
		move_past_next_semicolon(&current_command);
	}
	return (STATUS_OK);
}
