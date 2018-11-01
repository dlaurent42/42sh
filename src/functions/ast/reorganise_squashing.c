/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganise_squashing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 14:18:56 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/01 13:05:56 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			get_mallocs(int size, t_token_tree *new, t_token_tree *head)
{
	new->tokens = (char **)ft_memalloc(sizeof(char *) * (size + 1));
	new->blanks = (int *)ft_memalloc(sizeof(int) * (size));
	new->t_type = (int *)ft_memalloc(sizeof(int) * (size));
	if (!new->tokens || !new->blanks || !new->t_type)
	{
		free(new->tokens);
		free(new->blanks);
		free(new->t_type);
		return (false);
	}
	head->tokens = new->tokens;
	head->blanks = new->blanks;
	head->t_type = new->t_type;
	return (true);
}

static t_token_tree	*do_squash(
		t_token_tree *current_command,
		t_token_tree *track_command,
		t_token_tree *new,
		t_token_tree *follow)
{
	t_token_tree	*tmp;

	while (track_command && track_command->type == 0)
	{
		follow->tokens = track_command->tokens;
		follow->blanks = track_command->blanks;
		follow->t_type = track_command->t_type;
		while (*follow->tokens)
		{
			*(new->tokens++) = *(follow->tokens++);
			*(new->t_type++) = *(follow->t_type++);
			*(new->blanks++) = *(follow->blanks++);
		}
		tmp = track_command;
		track_command = track_command->right;
		free(tmp->tokens);
		free(tmp->blanks);
		free(tmp->t_type);
		if (tmp != current_command)
			free(tmp);
	}
	return (track_command);
}

static bool			get_new_token_array(t_token_tree *current_command,
		int size)
{
	t_token_tree	new;
	t_token_tree	head;
	t_token_tree	follow;
	t_token_tree	*track_command;

	track_command = current_command;
	if (!get_mallocs(size, &new, &head))
		return (false);
	track_command = do_squash(current_command, track_command, &new, &follow);
	current_command->right = track_command;
	current_command->tokens = head.tokens;
	current_command->t_type = head.t_type;
	current_command->blanks = head.blanks;
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
