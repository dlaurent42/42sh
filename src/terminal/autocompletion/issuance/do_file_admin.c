/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_file_admin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:15:36 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:58:26 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			get_mode(t_ac *ac, t_obj *head)
{
	t_obj			*obj;

	obj = head;
	while (ac->cmp_mode == MODE_NON && obj)
	{
		if (!obj->data.no_file)
			if (!ft_strncmp(obj->data.str, ac->file_name,
						ac->file_name_len))
				ac->cmp_mode = MODE_CMP;
		obj = obj->next;
	}
	obj = head;
	while (ac->cmp_mode == MODE_NON && obj)
	{
		if (!obj->data.no_file)
			if (ft_strstr(obj->data.str, ac->file_name))
				ac->cmp_mode = MODE_STR;
		obj = obj->next;
	}
}

static void			lock_files(t_ac *ac, t_obj *obj)
{
	while (obj)
	{
		if (ac->cmp_mode == MODE_CMP)
		{
			if (ft_strncmp(obj->data.str, ac->file_name,
						ac->file_name_len))
				obj->data.no_file = 1;
		}
		if (ac->cmp_mode == MODE_STR)
		{
			if (!ft_strstr(obj->data.str, ac->file_name))
				obj->data.no_file = 1;
		}
		if (!ft_strcmps(obj->data.str, "."))
			obj->data.no_file = 1;
		obj = obj->next;
	}
}

static void			get_column_widths(t_ac *ac, t_obj *obj)
{
	t_obj			*head;

	ac->len_file_name = 0;
	ac->items_to_display = 0;
	ac->total_blocks = 0;
	head = obj;
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

static void			issue_circular_pointers(t_ac *ac, t_obj *head)
{
	t_obj			*obj;
	t_obj			*track;

	while (head->next && head->data.no_file)
		head = head->next;
	obj = head;
	ac->select = head;
	ac->select->data.file_number = 0;
	while (obj && obj->next)
	{
		track = obj->next;
		while (track && track->data.no_file)
			track = track->next;
		if (!track)
			break ;
		track->ver_prev = obj;
		obj->ver_next = track;
		track->data.file_number = obj->data.file_number + 1;
		obj = track;
	}
	obj->ver_next = head;
	head->ver_prev = obj;
}

void				auto_do_file_admin(t_ac *ac, t_obj *obj)
{
	get_mode(ac, obj);
	lock_files(ac, obj);
	get_column_widths(ac, obj);
	issue_circular_pointers(ac, obj);
}
