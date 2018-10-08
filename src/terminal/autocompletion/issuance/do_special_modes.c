/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_special_modes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 23:59:47 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/09 01:19:58 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

static bool			gcc_check(char *str)
{
	if (!str
			|| !ft_strcmp(str, ".h")
			|| !ft_strcmp(str, ".c")
			|| !ft_strcmp(str, ".i")
			|| !ft_strcmp(str, ".ii")
			|| !ft_strcmp(str, ".cp")
			|| !ft_strcmp(str, ".cc")
			|| !ft_strcmp(str, ".cxx")
			|| !ft_strcmp(str, ".cpp")
			|| !ft_strcmp(str, ".c++")
			|| !ft_strcmp(str, ".C")
			|| !ft_strcmp(str, ".f")
			|| !ft_strcmp(str, ".for")
			|| !ft_strcmp(str, ".FOR")
			|| !ft_strcmp(str, ".F")
			|| !ft_strcmp(str, ".fpp")
			|| !ft_strcmp(str, ".FPP")
			|| !ft_strcmp(str, ".r")
			|| !ft_strcmp(str, ".s")
			|| !ft_strcmp(str, ".S"))
		return (true);
	return (false);
}

static void			filter_obj(t_obj *obj, int filter)
{
	while (obj)
	{
		if (filter == FILT_CD && !obj->data.dir)
			obj->data.no_file = 1;
		if (filter == FILT_GCC
				&& (!obj->data.dir && !gcc_check(ft_strrchr(obj->data.str, '.'))))
			obj->data.no_file = 1;
		obj = obj->next;
	}
}

void				auto_do_special_modes(t_shell *sh, t_obj *obj)
{
	char			*space;

	if (!(space = ft_strchr(sh->buffer.content, ' ')))
		return ;
	if (!ft_strncmp(sh->buffer.content, "cd", space - sh->buffer.content))
		filter_obj(obj, FILT_CD);
	else if (!ft_strncmp(sh->buffer.content, "gcc", space - sh->buffer.content))
		filter_obj(obj, FILT_GCC);
}
