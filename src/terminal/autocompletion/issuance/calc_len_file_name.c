/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 13:47:37 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/23 16:26:39 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				calc_len_file_name(t_frame *frame, t_args *args)
{
	int				len;
	char			*str;
	t_data			*data;

	len = 0;
	data = &args->data;
	str = data->str;
	while (str && *str)
	{
		if (((unsigned char)*str < 128))
			len++;
		else if ((*str & 0b11000000) == 0b11000000
				&& (*str & 0b00100000) != 0b00100000)
			len++;
		else if ((*str & 0b11100000) == 0b11100000
				&& (*str & 0b00010000) != 0b00010000)
			len++;
		else if ((*str & 0b11110000) == 0b11110000
				&& (*str & 0b00001000) != 0b00001000)
			len++;
		str++;
	}
	data->len_of_str = len;
	if (data->dir || data->lnk || data->sock || data->wht
				|| data->ifo || is_executeable(args))
		data->len_of_str++;
	len++;
	if (len > frame->len_file_name)
		frame->len_file_name = len;
}
