/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 17:18:49 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 07:04:15 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
# include "auto_completion.h"
# include "auto_completion_prot.h"

bool				auto_path(t_obj *obj, char *path, char *name)
{
	char			*new_path;
	char			*tmp;

	if ((obj->data.str = ft_strdup(name)))
		if ((new_path = ft_strnew(ft_strlen(path) + ft_strlen(name) + 1)))
		{
			tmp = new_path;
			if (ft_strcmp(path, "."))
			{
				while (path && *path)
					*(tmp++) = *(path++);
				*(tmp++) = '/';
			}
			while (name && *name)
				*(tmp++) = *(name++);
			obj->data.path = new_path;
		}
	if (!obj->data.str || !obj->data.path)
		return (false);
	return (true);
}
