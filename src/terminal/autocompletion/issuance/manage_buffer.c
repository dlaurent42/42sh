/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:27:35 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/02 17:27:51 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_manage_buffer(t_frame *frame, char *new_display_str)
{
	while (*new_display_str)
	{
		frame->shell->read->line[0] = *new_display_str;
		sh_fill_buffer(frame->shell);
		new_display_str++;
	}
	ft_bzero(frame->shell->read->line, 5);
}
