/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_special_modes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 23:59:47 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/15 19:05:02 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			gcc_check(char *str)
{
	if (str
		&& (!ft_strcmps(str, ".h")
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
				&& !obj->data.dir && !gcc_check(ft_strrchr(obj->data.str, '.')))
			obj->data.no_file = 1;
		obj = obj->next;
	}
}

void				auto_do_special_modes(t_shell *sh, t_obj *obj)
{
	char			*content;

	content = sh->buffer.content + sh->buffer.ushift;
	if (!ft_strncmp(move_past_leading_spaces(content), "cd ", 3))
		filter_obj(obj, FILT_CD);
	else if (!ft_strncmp(move_past_leading_spaces(content), "gcc ", 4)
			|| !ft_strncmp(move_past_leading_spaces(content), "cc ", 3))
		filter_obj(obj, FILT_GCC);
}
