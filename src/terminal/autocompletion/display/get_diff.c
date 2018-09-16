/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_diff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 19:58:55 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/14 23:53:09 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

int					get_diff(t_frame *frame, char *str, long long num, int flag)
{
	int				len;

	len = 1;
	if (str)
	{
		if (flag == LEN_NAME)
			return (frame->len_file_name - num);
	}
	return (0);
}
