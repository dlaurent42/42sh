/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 17:18:49 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/26 01:16:08 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void			*get_escaped_str(char *str)
{
	char			*new_str;
	char			*ptr;
	char			len;

	ptr = str;
	len = 0;
	while (*ptr && ++len)
	{
		if (glob_need_esc(*(ptr++)))
			len++;
	}
	if (!(new_str = ft_strnew(len)))
		return (NULL);
	ptr = new_str;
	while (*str)
	{
		if (glob_need_esc(*str))
			*(ptr++) = '\\';
		*(ptr++) = *(str++);
	}
	return (new_str);
}

bool				auto_path(t_obj *obj, char *path, char *name)
{
	char			*new_path;
	char			*tmp;

	obj->data.escaped_str = get_escaped_str(name);
	if ((obj->data.str = ft_strdup(name)))
		if ((new_path = ft_strnew(ft_strlen(path) + ft_strlen(name) + 1)))
		{
			tmp = new_path;
			while (path && *path)
				*(tmp++) = *(path++);
			*(tmp++) = '/';
			while (name && *name)
				*(tmp++) = *(name++);
			obj->data.path = new_path;
		}
	if (!obj->data.str || !obj->data.path || !obj->data.escaped_str)
	{
		free(obj->data.str);
		free(obj->data.path);
		free(obj->data.escaped_str);
		return (false);
	}
	return (true);
}
