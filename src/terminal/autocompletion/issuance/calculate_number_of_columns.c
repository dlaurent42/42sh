/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_number_of_columns.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 13:29:46 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 00:22:31 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool				auto_calculate_number_of_columns(t_shell *shell)
{
	int				column_width;
	struct winsize	window_size;

	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size) == -1)
		return (false);
	shell->ac->width = window_size.ws_col;
	shell->ac->height = window_size.ws_row;
	column_width = shell->ac->len_file_name + 1;
	shell->ac->number_of_columns = shell->ac->width / column_width;
	return (true);
}
