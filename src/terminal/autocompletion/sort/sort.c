/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/18 19:26:22 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/01 21:40:32 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			swap(t_frame *frame)
{
	t_data			tmp;

	if (frame->sort_function(frame))
	{
		tmp = frame->track->data;
		frame->track->data = frame->track->next->data;
		frame->track->next->data = tmp;
		return (true);
	}
	return (false);
}

static void			do_sort(t_frame *frame)
{
	bool			sorted;

	while (true)
	{
		frame->track = frame->head;
		sorted = true;
		while (frame->track && frame->track->next)
		{
			if (swap(frame))
				sorted = false;
			frame->track = frame->track->next;
		}
		if (sorted)
			break ;
	}
}

void				auto_sort(t_frame *frame)
{
	frame->sort_function = &auto_sort_alpha;
	frame->head = frame->current_args;
	do_sort(frame);
	frame->current_args = frame->head;
}
