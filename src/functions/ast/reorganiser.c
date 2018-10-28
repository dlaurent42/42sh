/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorganiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 22:54:42 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/28 15:16:55 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

		reorganise_command(current_command);

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
