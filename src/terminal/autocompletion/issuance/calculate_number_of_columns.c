/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_number_of_columns.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 13:29:46 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 02:15:21 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_calculate_number_of_columns(t_shell *shell)
{
	int				column_width;

	shell->ac->width = shell->window.width;
	shell->ac->height = shell->window.height;
	column_width = shell->ac->len_file_name + 1;
	if(!(shell->ac->number_of_columns = shell->ac->width / column_width))
		shell->ac->number_of_columns = 1;
}
