/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:24:19 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/28 16:06:45 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		error_file_descriptor(void)
{
	ft_putendl_fd("error: bad file descriptor", 2);
	return (1);
}

char		*get_front_descriptor(char *cmd, size_t len, int closed)
{
	char		*ret;

	if (!len || !(ret = ft_strndup(cmd, len)))
	{
		if (!(ret = ft_strdup(closed ? "1" : "0")))
			return (NULL);
	}
	return (ret);
}

char		*get_back_descriptor(char *cmd)
{
	char		*ret;

	if (!(ret = ft_strdup(cmd + 2)))
		return (NULL);
	return (ret);
}
