/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 12:16:42 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 18:43:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			print_end_char(t_obj *obj)
{
	if (obj->data.ifo)
		ft_putchar('|');
	else if (obj->data.dir)
		ft_putchar('/');
	else if (obj->data.lnk)
		ft_putchar('@');
	else if (obj->data.sock)
		ft_putchar('=');
	else if (obj->data.blk)
		ft_putchar('#');
	else if (obj->data.wht || obj->data.chr)
		ft_putchar('%');
	else if (auto_is_executeable(obj))
		ft_putchar('*');
}

static void			print_colour(t_shell *sh, t_obj *obj)
{
	if (auto_is_executeable(obj))
		ft_putstr(COL_EXE);
	if (obj->data.ifo)
		ft_putstr(COL_IFO);
	if (obj->data.chr)
		ft_putstr(COL_CHR);
	if (obj->data.dir)
		ft_putstr(COL_DIR);
	if (obj->data.blk)
		ft_putstr(COL_BLK);
	if (obj->data.reg && !auto_is_executeable(obj))
		ft_putstr(COL_REG);
	if (obj->data.lnk)
		ft_putstr(COL_LNK);
	if (obj->data.sock)
		ft_putstr(COL_SOCK);
	if (obj == sh->ac->select)
		ft_putstr(COL_BG);
	ft_printf("%.*s", sh->window.width - 1, obj->data.str);
}

void				auto_file_name(t_shell *sh, t_obj *obj)
{
	print_colour(sh, obj);
	if (obj != sh->ac->select)
		ft_putstr(COL_CLR);
	print_end_char(obj);
	if (sh->ac->number_of_columns > 1)
		auto_print_spaces(sh->ac->len_file_name - obj->data.len_of_str + 1);
	ft_putstr(COL_CLR);
}
