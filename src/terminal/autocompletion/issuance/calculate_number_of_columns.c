/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_number_of_columns.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 13:29:46 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/07 23:27:16 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				auto_calculate_number_of_columns(t_ac *ac)
{
	int				column_width;
	struct winsize	window_size;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1)
		return (false);
	ac->width = window_size.ws_col;
	ac->height = window_size.ws_row;
	column_width = ac->len_file_name + 1;
	ac->number_of_columns = ac->width / column_width;
	return (true);
}
