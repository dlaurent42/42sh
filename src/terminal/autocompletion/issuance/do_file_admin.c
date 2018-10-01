/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_file_admin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:15:36 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/01 21:14:54 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			get_mode(t_frame *frame, t_args *head)
{
	t_args			*args;

	args = head;
	while (frame->cmp_mode == MODE_NON && args)
	{
		if (!args->data.no_file)
			if (!ft_strncmp(args->data.str, frame->file_name,
						frame->file_name_len))
				frame->cmp_mode = MODE_CMP;
		args = args->next;
	}
	args = head;
	while (frame->cmp_mode == MODE_NON && args)
	{
		if (!args->data.no_file)
			if (ft_strstr(args->data.str, frame->file_name))
				frame->cmp_mode = MODE_STR;
		args = args->next;
	}
}

static void			lock_files(t_frame *frame, t_args *args)
{
	while (args)
	{
		if (frame->cmp_mode == MODE_CMP)
		{
			if (ft_strncmp(args->data.str, frame->file_name,
						frame->file_name_len))
				args->data.no_file = 1;
		}
		if (frame->cmp_mode == MODE_STR)
		{
			if (!ft_strstr(args->data.str, frame->file_name))
				args->data.no_file = 1;
		}
		if (!ft_strcmps(args->data.str, "."))
			args->data.no_file = 1;
		args = args->next;
	}
}

static void			get_column_widths(t_frame *frame, t_args *args)
{
	t_args			*head;

	frame->len_file_name = 0;
	frame->items_to_display = 0;
	frame->total_blocks = 0;
	head = args;
	while (head)
	{
		if (!head->data.no_file)
		{
			auto_calc_len_file_name(frame, head);
			head->data.file_number = frame->items_to_display;
			frame->items_to_display++;
		}
		head = head->next;
	}
}

static void			issue_circular_pointers(t_frame *frame, t_args *head)
{
	t_args			*args;
	t_args			*track;

	while (head->next && head->data.no_file)
		head = head->next;
	args = head;
	frame->select = head;
	while (args && args->next)
	{
		track = args->next;
		while (track && track->data.no_file)
			track = track->next;
		if (!track)
			break ;
		track->show_prev = args;
		args->show_next = track;
		args = track;
	}
	args->show_next = head;
	head->show_prev = args;
}

void				auto_do_file_admin(t_frame *frame, t_args *args)
{
	get_mode(frame, args);
	lock_files(frame, args);
	get_column_widths(frame, args);
	issue_circular_pointers(frame, args);
}
