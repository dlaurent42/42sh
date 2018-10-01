/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issuance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 11:55:05 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/01 08:34:06 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_issuance(t_frame *frame)
{
	if (frame->auto_mode == AUTO_BIN)
	{
		if(!(frame->file_name = ft_strdup(frame->argv[1])))
			return ;
		frame->file_name_len = ft_strlen(frame->file_name);
		auto_loop_valid_dir(frame, frame->args);
	}
	else if (frame->auto_mode == AUTO_REG)
	{
		frame->current_args = frame->args;
		if (!auto_get_attributes(frame))
			return ;
		auto_sort(frame);
		frame->args = frame->current_args;
		auto_loop_dirs(frame);
	}
}
