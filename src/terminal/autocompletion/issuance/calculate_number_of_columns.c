/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_number_of_columns.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 13:29:46 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/02 10:26:23 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				auto_calculate_number_of_columns(t_frame *frame)
{
	int				column_width;
	struct winsize	window_size;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1)
		return (false);
	frame->width = window_size.ws_col;
	frame->height = window_size.ws_row;
	column_width = frame->len_file_name + 1;
	frame->number_of_columns = frame->width / column_width;
	return (true);
}
