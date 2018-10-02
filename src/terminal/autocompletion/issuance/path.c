/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 17:18:49 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/02 14:38:08 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				auto_path(t_args *args, char *path, char *name)
{
	char			*new_path;
	char			*tmp;

	if ((args->data.str = ft_strdup(name)))
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
			args->data.path = new_path;
		}
	if (!args->data.str || !args->data.path)
		return (false);
	return (true);
}
