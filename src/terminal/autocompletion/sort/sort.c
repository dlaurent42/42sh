/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 19:26:22 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 06:33:22 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
# include "auto_completion.h"

static bool			swap(t_shell *shell)
{
	t_data			tmp;

	if (auto_sort_alpha(shell))
	{
		tmp = shell->ac->track->data;
		shell->ac->track->data = shell->ac->track->next->data;
		shell->ac->track->next->data = tmp;
		return (true);
	}
	return (false);
}

static void			do_sort(t_shell *shell)
{
	bool			sorted;

	while (true)
	{
		shell->ac->track = shell->ac->head;
		sorted = true;
		while (shell->ac->track && shell->ac->track->next)
		{
			if (swap(shell))
				sorted = false;
			shell->ac->track = shell->ac->track->next;
		}
		if (sorted)
			break ;
	}
}

void				auto_sort(t_shell *shell)
{
	shell->ac->head = shell->ac->current_obj;
	do_sort(shell);
	shell->ac->current_obj = shell->ac->head;
}
