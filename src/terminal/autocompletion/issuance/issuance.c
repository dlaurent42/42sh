/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   issuance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 11:55:05 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/01 21:48:32 by dhojt            ###   ########.fr       */
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
		auto_show_screen(frame, frame->args);
	}
	else
	{
		frame->current_args = frame->args;
		if (!auto_get_attributes(frame))
			return ;
		frame->args = frame->current_args;
		if (frame->args->data.dir && !frame->args->data.no_file)
			auto_do_ls(frame, frame->args);
	}
}
