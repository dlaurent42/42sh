/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:24:19 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/31 21:55:10 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		error_file_descriptor(char **back)
{
	ft_putstr_fd("sh: ", 2);
	ft_putstr_fd(*back, 2);
	ft_putendl_fd(": bad file descriptor", 2);
	ft_strdel(back);
	return (STATUS_ERR);
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
