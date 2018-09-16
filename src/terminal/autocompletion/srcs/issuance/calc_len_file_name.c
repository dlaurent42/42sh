/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_len_file_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 13:47:37 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/14 23:53:56 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "auto_completion.h"

void				calc_len_file_name(t_frame *frame, t_args *args)
{
	int				len;
	t_data			*data;

	data = &args->data;
	len = ft_strlen(data->str);
	data->len_of_str = len;
	if (data->dir || data->lnk || data->sock || data->wht
				|| data->ifo || is_executeable(args))
		data->len_of_str++;
	len++;
	if (len > frame->len_file_name)
		frame->len_file_name = len;
}
