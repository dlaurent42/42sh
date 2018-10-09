/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 20:03:57 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/09 13:54:21 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

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

static void			do_loop(t_shell *sh, t_obj *head)
{
	t_obj			*obj;

	obj = head;
	while (sh->modes.auto_completion)
	{
		obj = head;
		delete_str(sh);
		sh_print_str(sh, sh->ac->select->data.str);
		if (sh->ac->select->ver_next == sh->ac->select)
		{
			sh_print_str(sh, (sh->ac->select->data.dir) ? "/" : " ");
			break ;
		}
		auto_display(sh, obj);
		read(0, sh->read->line, 4);
		if (sh->read->line[0] == 4)
			break ;
		auto_read_dispatcher(sh);
		ft_bzero(sh->read->line, LINE_SIZE);
	}
}

void				auto_show_screen(t_shell *sh, t_obj *obj)
{
	auto_do_special_modes(sh, obj);
	auto_do_file_admin(sh, obj);
	if (sh->ac->cmp_mode == MODE_NON)
		return ;
	sh->ac->del_file_name = sh->ac->file_name;
	if (sh->ac->auto_mode == AUTO_WILD)
		fill_buffer_with_wild(sh, obj);
	else
		do_loop(sh, obj);
}
