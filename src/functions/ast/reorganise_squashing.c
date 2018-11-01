/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganise_squashing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:18:56 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/01 12:16:04 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			get_new_token_array(t_token_tree *current_command,
		int size)
{
	char			**tokens_head;
	char			**track_tokens;
	int				*blanks_head;
	int				*track_blanks;
	int				*t_type_head;
	int				*track_t_type;
	t_token_tree	new;
	t_token_tree	*tmp;
	t_token_tree	*track_command;

	new.tokens = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	new.blanks = (int *)ft_memalloc(sizeof(int) * (size));
	new.t_type = (int *)ft_memalloc(sizeof(int) * (size));
	if (!new.tokens || !new.blanks || !new.t_type)
	{
		free(new.tokens);
		free(new.blanks);
		free(new.t_type);
		return (false);
	}
	tokens_head = new.tokens;
	blanks_head = new.blanks;
	t_type_head = new.t_type;
	track_command = current_command;
	while (track_command && track_command->type == 0)
	{
		track_tokens = track_command->tokens;
		track_blanks = track_command->blanks;
		track_t_type = track_command->t_type;
		while (*track_tokens)
		{
			*(new.tokens++) = *(track_tokens++);
			*(new.t_type++) = *(track_t_type++);
			*(new.blanks++) = *(track_blanks++);
		}
		tmp = track_command;
		track_command = track_command->right;
		free(tmp->tokens);
		free(tmp->blanks);
		free(tmp->t_type);
		if (tmp != current_command)
			free(tmp);
	}
	current_command->right = track_command;
	current_command->tokens = tokens_head;
	current_command->t_type = t_type_head;
	current_command->blanks = blanks_head;
	return (true);
}

bool				squash_type_zero(t_token_tree *current_command)
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
