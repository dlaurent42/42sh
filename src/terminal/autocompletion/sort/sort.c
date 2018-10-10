/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 19:26:22 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/10 08:20:56 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

bool				sort_alpha(t_obj *track)
{
	if (ft_strcmp(track->data.str, track->next->data.str) > 0)
		return (true);
	return (false);
}

static bool			swap(t_obj *track)
{
	t_data			tmp;

	if (sort_alpha(track))
	{
		tmp = track->data;
		track->data = track->next->data;
		track->next->data = tmp;
		return (true);
	}
	return (false);
}

void				auto_sort(t_obj *obj)
{
	bool			sorted;
	t_obj			*track;

	while (true)
	{
		track = obj;
		sorted = true;
		while (track && track->next)
		{
			if (swap(track))
				sorted = false;
			track = track->next;
		}
		if (sorted)
			break ;
	}
}
