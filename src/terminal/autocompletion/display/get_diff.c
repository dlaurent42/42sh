/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_diff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:58:55 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/20 22:52:24 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int					get_diff(t_frame *frame, char *str, long long num, int flag)
{
	if (str)
	{
		if (flag == LEN_NAME)
			return (frame->len_file_name - num);
	}
	return (0);
}
