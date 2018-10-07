/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:03:57 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:27:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			delete_str(t_ac *ac)
{
	int				len;

	len = ft_strlenu(ac->del_file_name);
	while (len--)
		sh_delete_char(ac->shell);
}

static void			fill_buffer_with_wild(t_ac *ac, t_args *args)
{
	ac->del_file_name = ac->args->data.path;
	delete_str(ac);
	while (args)
	{
		if (!args->data.no_file && *args->data.str != '.')
		{
			auto_manage_buffer(ac->shell, args->data.path);
			auto_manage_buffer(ac->shell, " ");
		}
		args = args->next;
	}
}

static void			do_loop(t_ac *ac, t_args *head)
{
	t_args			*args;

	args = head;
	while (ac->shell->modes.auto_completion)
	{
		if (!auto_calculate_number_of_columns(ac))
			break ;
		args = head;
		delete_str(ac);
		auto_manage_buffer(ac->shell, ac->select->data.str);
		if (ac->select->ver_next == ac->select)
		{
			auto_manage_buffer(ac->shell, (ac->select->data.dir) ? "/" : " ");
			break ;
		}
		auto_display(ac, args);
		read(0, ac->shell->read->line, 4);
		if (ac->shell->read->line[0] == 4)
			break ;
		auto_read_dispatcher(ac);
		ft_bzero(ac->shell->read->line, LINE_SIZE);
	}
}

void				auto_show_screen(t_ac *ac, t_args *args)
{
	auto_do_file_admin(ac, args);
	if (ac->cmp_mode == MODE_NON)
		return ;
	ac->del_file_name = ac->file_name;
	if (ac->auto_mode == AUTO_WILD)
		fill_buffer_with_wild(ac, args);
	else
		do_loop(ac, args);
}
