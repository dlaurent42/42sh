/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_special_modes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 23:59:47 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/09 01:24:19 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

static bool			gcc_check(char *str)
{
	if (str
		&&	( !ft_strcmps(str, ".h")
			|| !ft_strcmps(str, ".c")
			|| !ft_strcmps(str, ".i")
			|| !ft_strcmps(str, ".ii")
			|| !ft_strcmps(str, ".cp")
			|| !ft_strcmps(str, ".cc")
			|| !ft_strcmps(str, ".cxx")
			|| !ft_strcmps(str, ".cpp")
			|| !ft_strcmps(str, ".c++")
			|| !ft_strcmps(str, ".C")
			|| !ft_strcmps(str, ".f")
			|| !ft_strcmps(str, ".for")
			|| !ft_strcmps(str, ".FOR")
			|| !ft_strcmps(str, ".F")
			|| !ft_strcmps(str, ".fpp")
			|| !ft_strcmps(str, ".FPP")
			|| !ft_strcmps(str, ".r")
			|| !ft_strcmps(str, ".s")
			|| !ft_strcmps(str, ".S")))
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
