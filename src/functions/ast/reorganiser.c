/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/28 19:09:49 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			**get_new_token_array(t_token_tree *current_command)
{
	int				size;
	char			**tokens;
	char			**tokens_head;
	char			**track_tokens;
	t_token_tree	*track_command;

	size = 0;
	track_command = current_command;
	//CALCULATE SIZE OF ARRAY
	while (track_command && track_command->type == 0)
	{
		track_tokens = track_command->tokens;
		while (*track_tokens && ++size)
			track_tokens++;
		track_command = track_command->right;
	}
	if (!(tokens = (char **)ft_memalloc(sizeof(char *) * (size + 1))))
		return (NULL);
	tokens_head = tokens;
	//FILL NEW ARRAY:
	track_command = current_command;
	while (track_command && track_command->type == 0)
	{
		track_tokens = track_command->tokens;
		while (*track_tokens)
		{
			*tokens = *track_tokens;
			tokens++;
			track_tokens++;
		}
		track_command = track_command->right;
	}
	free(current_command->tokens);
	return (tokens_head);
}

static char			**squash_type_zero(t_token_tree *current_command)
{
	int				len;
	char			**tokens;
	t_token_tree	*track;

	len = 0;
	tokens = NULL;//Need this?
	track = current_command;
	while (track && track->type == 0 && ++len)
		track = track->right;
	if (len > 1)
		return (get_new_token_array(current_command));
	return (current_command->tokens);
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

void				reorganise_tokens(t_token_tree **list)//Change to bool
{
	t_token_tree	*current_command;

	current_command = *list;
	while (current_command)
	{
		reorganise_command(current_command);
		if (!(current_command->tokens = squash_type_zero(current_command)))
			return ;//NULL
		move_to_next_command(&current_command);
	}
}
