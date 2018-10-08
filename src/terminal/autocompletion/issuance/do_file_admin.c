/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_file_admin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:15:36 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 06:33:22 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
# include "auto_completion.h"

static void			get_mode(t_shell *shell, t_obj *head)
{
	t_obj			*obj;

	obj = head;
	while (shell->ac->cmp_mode == MODE_NON && obj)
	{
		if (!obj->data.no_file)
			if (!ft_strncmp(obj->data.str, shell->ac->file_name,
						shell->ac->file_name_len))
				shell->ac->cmp_mode = MODE_CMP;
		obj = obj->next;
	}
	obj = head;
	while (shell->ac->cmp_mode == MODE_NON && obj)
	{
		if (!obj->data.no_file)
			if (ft_strstr(obj->data.str, shell->ac->file_name))
				shell->ac->cmp_mode = MODE_STR;
		obj = obj->next;
	}
}

static void			lock_files(t_shell *shell, t_obj *obj)
{
	while (obj)
	{
		if (shell->ac->cmp_mode == MODE_CMP)
		{
			if (ft_strncmp(obj->data.str, shell->ac->file_name,
						shell->ac->file_name_len))
				obj->data.no_file = 1;
		}
		if (shell->ac->cmp_mode == MODE_STR)
		{
			if (!ft_strstr(obj->data.str, shell->ac->file_name))
				obj->data.no_file = 1;
		}
		if (!ft_strcmps(obj->data.str, "."))
			obj->data.no_file = 1;
		obj = obj->next;
	}
}

static void			get_column_widths(t_shell *shell, t_obj *obj)
{
	t_obj			*head;

	shell->ac->len_file_name = 0;
	shell->ac->items_to_display = 0;
	shell->ac->total_blocks = 0;
	head = obj;
	while (head)
	{
		if (!head->data.no_file)
		{
			auto_calc_len_file_name(shell, head);
			head->data.file_number = shell->ac->items_to_display;
			shell->ac->items_to_display++;
		}
		head = head->next;
	}
}

static void			issue_circular_pointers(t_shell *shell, t_obj *head)
{
	t_obj			*obj;
	t_obj			*track;

	while (head->next && head->data.no_file)
		head = head->next;
	obj = head;
	shell->ac->select = head;
	shell->ac->select->data.file_number = 0;
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

void				auto_do_file_admin(t_shell *shell, t_obj *obj)
{
	get_mode(shell, obj);
	lock_files(shell, obj);
	get_column_widths(shell, obj);
	issue_circular_pointers(shell, obj);
}
