/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.folder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/16 15:07:52 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/16 17:01:50 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*term_get_folder_name(t_env *env, char *location, size_t length)
{
	if (ft_strcmps((char *)location, env_search(env, "HOME")) == 0)
		return (ft_strdup("\e[1;32;40m~"));
	if (length == 1 && location[0] == '/')
		return (ft_strdup("\e[1;32;40m/"));
	(location[length - 1] == '/') ? location[length--] = '\0' : 0;
	if ((location[0] == '/' && ft_strcountif((char *)location, '/') == 1))
		return (ft_strjoins("\e[1;32;40m", location));
	length--;
	while (location[length] && location[length] != '/')
		length--;
	return (ft_strjoins("\e[1;32;40m", location + length + 1));
}
