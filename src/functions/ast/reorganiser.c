/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/28 18:42:19 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			**get_new_token_array(t_token_tree *current_command)
{
	int				size;
	char			**tokens;
	char			**track_tokens;
	t_token_tree	*track_command;

	size = 0;
	track_command = current_command;
	while (track_command && track_command->type == 0)
	{
		track_tokens = track_command->tokens;
		while (*track_tokens && ++size)
			track_tokens++;
		track_command = track_command->right;
	}
	if (!(tokens = (char **)memmalloc(sizeof(char *) * (size + 1))))
		return (NULL);

	//FILL NEW ARRAY:
	track_command = current_command;
	while (track_command && track_command->type == 0)
	{
		track_tokens = track_command->tokens;
		while (*track_tokens)
		{
			token
			track_tokens++;
		}
		track_command = track_command->right;
	}
	ft_printf("\n\nSIZE:[%d]\n\n", size);
	return (NULL);
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
		if (!squash_type_zero(current_command))
			;//return BAD HIT HAPPENED.
		move_to_next_command(&current_command);
	}
}
