/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 19:45:44 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/02 21:50:43 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*backtick_capture(int fd)
{
	int			len;
	char		*ret;
	char		buff[BACKTICK_BUFF + 1];

	ret = NULL;
	ft_bzero((char *)buff, BACKTICK_BUFF + 1);
	while ((len = read(fd, buff, BACKTICK_BUFF)) == BACKTICK_BUFF)
	{
		ret = ft_strjoinf(ret, buff, 1);
		ft_bzero((char *)buff, len);
	}
	ret = ft_strjoinf(ret, buff, 1);
	ft_bzero((char *)buff, len);
	return (ret);
}
