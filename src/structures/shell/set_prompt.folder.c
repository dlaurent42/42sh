/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.folder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:07:52 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 16:06:48 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_get_folder_name(t_env *env, char *location, size_t len)
{
	if (env_search(env, "HOME")
	&& ft_strcmps(location, env_search(env, "HOME")) == 0)
		return (ft_strjoins(COL_FOLDER, "~"));
	if (len == 1 && location[0] == '/')
		return (ft_strjoins(COL_FOLDER, "/"));
	(location[len - 1] == '/') ? location[len--] = '\0' : 0;
	if ((location[0] == '/' && ft_strcountif(location, '/') == 1))
		return (ft_strjoins(COL_FOLDER, location));
	len--;
	while (location[len] && location[len] != '/')
		len--;
	return (ft_strjoins(COL_FOLDER, location + len + 1));
}
