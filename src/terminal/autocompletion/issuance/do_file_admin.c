/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_file_admin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:15:36 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:27:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			get_mode(t_ac *ac, t_args *head)
{
	t_args			*args;

	args = head;
	while (ac->cmp_mode == MODE_NON && args)
	{
		if (!args->data.no_file)
			if (!ft_strncmp(args->data.str, ac->file_name,
						ac->file_name_len))
				ac->cmp_mode = MODE_CMP;
		args = args->next;
	}
	args = head;
	while (ac->cmp_mode == MODE_NON && args)
	{
		if (!args->data.no_file)
			if (ft_strstr(args->data.str, ac->file_name))
				ac->cmp_mode = MODE_STR;
		args = args->next;
	}
}

static void			lock_files(t_ac *ac, t_args *args)
{
	while (args)
	{
		if (ac->cmp_mode == MODE_CMP)
		{
			if (ft_strncmp(args->data.str, ac->file_name,
						ac->file_name_len))
				args->data.no_file = 1;
		}
		if (ac->cmp_mode == MODE_STR)
		{
			if (!ft_strstr(args->data.str, ac->file_name))
				args->data.no_file = 1;
		}
		if (!ft_strcmps(args->data.str, "."))
			args->data.no_file = 1;
		args = args->next;
	}
}

static void			get_column_widths(t_ac *ac, t_args *args)
{
	t_args			*head;

	ac->len_file_name = 0;
	ac->items_to_display = 0;
	ac->total_blocks = 0;
	head = args;
	while (head)
	{
		if (!head->data.no_file)
		{
			auto_calc_len_file_name(ac, head);
			head->data.file_number = ac->items_to_display;
			ac->items_to_display++;
		}
		head = head->next;
	}
}

static void			issue_circular_pointers(t_ac *ac, t_args *head)
{
	t_args			*args;
	t_args			*track;

	while (head->next && head->data.no_file)
		head = head->next;
	args = head;
	ac->select = head;
	ac->select->data.file_number = 0;
	while (args && args->next)
	{
		track = args->next;
		while (track && track->data.no_file)
			track = track->next;
		if (!track)
			break ;
		track->ver_prev = args;
		args->ver_next = track;
		track->data.file_number = args->data.file_number + 1;
		args = track;
	}
	args->ver_next = head;
	head->ver_prev = args;
}

void				auto_do_file_admin(t_ac *ac, t_args *args)
{
	get_mode(ac, args);
	lock_files(ac, args);
	get_column_widths(ac, args);
	issue_circular_pointers(ac, args);
}
