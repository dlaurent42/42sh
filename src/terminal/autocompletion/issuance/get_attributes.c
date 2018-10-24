/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 12:25:28 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 08:02:51 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			get_sym_path(t_obj *obj)
{
	int				len;
	t_data			*data;

	data = &obj->data;
	if ((len = readlink(data->path, data->sym_path, RL_BUFSIZE)) != -1)
		data->sym_path[len] = '\0';
}

static void			get_type(t_obj *obj)
{
	int				type;

	type = obj->data.type;
	if ((TYPE_LNK & type) == TYPE_LNK)
	{
		obj->data.lnk = 1;
		get_sym_path(obj);
	}
	else if ((TYPE_SOCK & type) == TYPE_SOCK)
		obj->data.sock = 1;
	else if ((TYPE_REG & type) == TYPE_REG)
		obj->data.reg = 1;
	else if ((TYPE_WHT & type) == TYPE_WHT)
		obj->data.wht = 1;
	else if ((TYPE_IFO & type) == TYPE_IFO)
		obj->data.ifo = 1;
	else if ((TYPE_CHR & type) == TYPE_CHR)
		obj->data.chr = 1;
	else if ((TYPE_DIR & type) == TYPE_DIR)
		obj->data.dir = 1;
	if ((TYPE_BLK & type) == TYPE_BLK)
		obj->data.blk = 1;
}

static void			read_f(t_shell *sh, t_obj *obj, struct stat *f)
{
	sh->ac->total_blocks += f->st_blocks;
	obj->data.mode = f->st_mode;
	obj->data.type = f->st_mode;
	obj->data.links = f->st_nlink;
	obj->data.rdev = f->st_rdev;
	get_type(obj);
}

static bool			get_initial(t_shell *sh, t_obj *obj)
{
	char			*slash;
	struct stat		f;

	slash = ft_strrchr(obj->data.path, '/');
	obj->data.parent_path = (slash)
		? ft_strndup(obj->data.path, slash - obj->data.path)
		: ft_strdup(".");
	if (ft_strcmps(obj->data.str, "."))
		sh->ac->file_name = ft_strdup((slash) ? slash + 1 : obj->data.str);
	else
		sh->ac->file_name = ft_strdup((slash) ? slash + 1 : "");
	if (!obj->data.parent_path || !sh->ac->file_name)
		return (false);
	if (!ft_strcmps(sh->ac->file_name, "*"))
	{
		sh->ac->auto_mode = AUTO_WILD;
		*sh->ac->file_name = '\0';
	}
	if (!lstat(obj->data.parent_path, &f))
		read_f(sh, obj, &f);
	else
		obj->data.no_file = 1;
	return (true);
}

bool				auto_get_attributes(t_shell *sh)
{
	t_obj			*obj;
	struct stat		f;

	if (sh->ac->at_mode == AT_FIRST)
	{
		if (!get_initial(sh, sh->ac->current_obj))
			return (false);
	}
	else
	{
		obj = sh->ac->current_obj;
		while (obj)
		{
			if (!lstat(obj->data.path, &f))
				read_f(sh, obj, &f);
			else
				obj->data.no_file = 1;
			obj = obj->next;
		}
	}
	sh->ac->at_mode = AT_REST;
	return (true);
}
