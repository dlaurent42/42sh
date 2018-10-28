/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/28 17:33:19 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
static char			**squash_type_zero(t_toke_tree *current_command)
{
	int				len;
	char			**tokens;
	t_token_tree	*track;

	len = 0;
	tokens = NULL;
	track = current_command;
	while (track && track->type == 0 && ++len)
		track = track->right;
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
		move_to_next_command(&current_command);
	}
}
