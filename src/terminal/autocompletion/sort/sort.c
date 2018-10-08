/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 19:26:22 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 08:43:52 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

static bool			swap(t_shell *sh)
{
	t_data			tmp;

	if (auto_sort_alpha(sh))
	{
		tmp = sh->ac->track->data;
		sh->ac->track->data = sh->ac->track->next->data;
		sh->ac->track->next->data = tmp;
		return (true);
	}
	return (false);
}

static void			do_sort(t_shell *sh)
{
	bool			sorted;

	while (true)
	{
		sh->ac->track = sh->ac->head;
		sorted = true;
		while (sh->ac->track && sh->ac->track->next)
		{
			if (swap(sh))
				sorted = false;
			sh->ac->track = sh->ac->track->next;
		}
		if (sorted)
			break ;
	}
}

void				auto_sort(t_shell *sh)
{
	sh->ac->head = sh->ac->current_obj;
	do_sort(sh);
	sh->ac->current_obj = sh->ac->head;
}
