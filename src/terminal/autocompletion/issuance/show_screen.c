/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:03:57 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/07 17:12:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			delete_str(t_shell *sh)
{
	int				len;

	len = ft_strlenu(sh->ac->del_file_name);
	while (len--)
		sh_delete_char(sh);
}

static void			fill_buffer_with_wild(t_shell *sh, t_obj *obj)
{
	sh->ac->del_file_name = sh->ac->obj->data.path;
	delete_str(sh);
	while (obj)
	{
		if (!obj->data.no_file && *obj->data.str != '.')
		{
			sh_print_str(sh, obj->data.path);
			sh_print_str(sh, " ");
		}
		obj = obj->next;
	}
}

static void			do_loop_if(t_shell *sh)
{
	if (sh->ac->select->data.dir)
		sh_print_str(sh, "/");
	else if (sh->ac->select->data.env && sh->ac->auto_mode != AUTO_ENV)
		sh_print_str(sh, "=");
	else
		sh_print_str(sh, " ");
}

static void			do_loop(t_shell *sh, t_obj *head)
{
	t_obj			*obj;
	bool			first_print;

	obj = head;
	first_print = true;
	while (sh->modes.auto_completion)
	{
		obj = head;
		delete_str(sh);
		sh_print_str(sh, sh->ac->select->data.escaped_str);
		if (sh->ac->select->ver_next == sh->ac->select)
		{
			do_loop_if(sh);
			break ;
		}
		auto_display(sh, obj, first_print);
		first_print = false;
		read(0, sh->read->line, 4);
		auto_read_dispatcher(sh);
		ft_bzero(sh->read->line, LINE_SIZE);
	}
}

void				auto_show_screen(t_shell *sh, t_obj *obj)
{
	auto_do_file_admin(sh, obj);
	if (sh->ac->cmp_mode == MODE_NON)
		return ;
	sh->ac->del_file_name = sh->ac->file_name;
	if (sh->ac->auto_mode == AUTO_WILD)
		fill_buffer_with_wild(sh, obj);
	else
		do_loop(sh, obj);
}
