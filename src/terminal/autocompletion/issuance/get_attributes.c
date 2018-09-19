/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 12:25:28 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/17 08:43:43 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>

static void			get_sym_path(t_args *args)
{
	int				len;
	t_data			*data;

	data = &args->data;
	if ((len = readlink(data->path, data->sym_path, RL_BUFSIZE)) != -1)
		data->sym_path[len] = '\0';
}

static void			get_type(t_args *args)
{
	int				type;

	type = args->data.type;
	if ((TYPE_LNK & type) == TYPE_LNK)
	{
		args->data.lnk = 1;
		get_sym_path(args);
	}
	else if ((TYPE_SOCK & type) == TYPE_SOCK)
		args->data.sock = 1;
	else if ((TYPE_REG & type) == TYPE_REG)
		args->data.reg = 1;
	else if ((TYPE_WHT & type) == TYPE_WHT)
		args->data.wht = 1;
	else if ((TYPE_IFO & type) == TYPE_IFO)
		args->data.ifo = 1;
	else if ((TYPE_CHR & type) == TYPE_CHR)
		args->data.chr = 1;
	else if ((TYPE_DIR & type) == TYPE_DIR)
		args->data.dir = 1;
	if ((TYPE_BLK & type) == TYPE_BLK)
		args->data.blk = 1;
}

static void			read_f(t_frame *frame, t_args *args, struct stat *f)
{
	frame->total_blocks += f->st_blocks;
	args->data.mode = f->st_mode;
	args->data.type = f->st_mode;
	args->data.links = f->st_nlink;
	args->data.rdev = f->st_rdev;
	get_type(args);
}

static void			get_initial(t_frame *frame, t_args *args)
{
	char			*slash;
	struct stat		f;

	while (args)
	{
		slash = ft_strrchr(args->data.path, '/');
		args->data.parent_path = (slash)
			? ft_strndup(args->data.path, slash - args->data.path)
			: ft_strdup(".");
		if (ft_strcmp(args->data.str, "."))
			frame->file_name = ft_strdup((slash) ? slash + 1 : args->data.str);
		else
			frame->file_name = ft_strdup((slash) ? slash + 1 : "");
		if (!args->data.parent_path)
			args->data.parent_path = frame->malloc_failed;
		if (!frame->file_name)
			frame->file_name = frame->malloc_failed;
		frame->file_name_len = ft_strlen(frame->file_name);
		if (!lstat(args->data.parent_path, &f))
			read_f(frame, args, &f);
		else
			args->data.no_file = 1;
		args = args->next;
	}
}

void				get_attributes(t_frame *frame)
{
	t_args			*args;
	struct stat		f;

	if (frame->at_mode == AT_FIRST)
		get_initial(frame, frame->current_args);
	else
	{
		args = frame->current_args;
		while (args)
		{
			if (!lstat(args->data.path, &f))
				read_f(frame, args, &f);
			else
				args->data.no_file = 1;
			args = args->next;
		}
	}
	frame->at_mode = AT_REST;
}
