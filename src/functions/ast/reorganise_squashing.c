/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganise_squashing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:18:56 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/31 14:19:13 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			**get_new_token_array(t_token_tree *current_command,
		int size)
{
	char			**tokens;
	char			**tokens_head;
	char			**track_tokens;
	t_token_tree	*tmp;
	t_token_tree	*track_command;

	if (!(tokens = (char **)ft_memalloc(sizeof(char *) * (size + 1))))
		return (NULL);
	tokens_head = tokens;
	track_command = current_command;
	while (track_command && track_command->type == 0)
	{
		track_tokens = track_command->tokens;
		while (*track_tokens)
			*(tokens++) = *(track_tokens++);
		tmp = track_command;
		track_command = track_command->right;
		free(tmp->tokens);
		if (tmp != current_command)
			free(tmp);
	}
	current_command->right = track_command;
	return (tokens_head);
}

char				**squash_type_zero(t_token_tree *current_command)
{
	int				len;
	int				size;
	char			**track_tokens;
	t_token_tree	*track;

	len = 0;
	size = 0;
	track = current_command;
	while (track && track->type == 0 && ++len)
		track = track->right;
	if (len > 1)
	{
		track = current_command;
		while (track && track->type == 0)
		{
			track_tokens = track->tokens;
			while (*track_tokens && ++size)
				track_tokens++;
			track = track->right;
		}
		return (get_new_token_array(current_command, size));
	}
	return (current_command->tokens);
}
