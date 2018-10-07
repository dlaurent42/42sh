/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 19:26:22 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:27:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			swap(t_ac *ac)
{
	t_data			tmp;

	if (ac->sort_function(ac))
	{
		tmp = ac->track->data;
		ac->track->data = ac->track->next->data;
		ac->track->next->data = tmp;
		return (true);
	}
	return (false);
}

static void			do_sort(t_ac *ac)
{
	bool			sorted;

	while (true)
	{
		ac->track = ac->head;
		sorted = true;
		while (ac->track && ac->track->next)
		{
			if (swap(ac))
				sorted = false;
			ac->track = ac->track->next;
		}
		if (sorted)
			break ;
	}
}

void				auto_sort(t_ac *ac)
{
	ac->sort_function = &auto_sort_alpha;
	ac->head = ac->current_args;
	do_sort(ac);
	ac->current_args = ac->head;
}
