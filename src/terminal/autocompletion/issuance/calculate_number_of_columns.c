/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_number_of_columns.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 13:29:46 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 22:19:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_calculate_number_of_columns(t_shell *sh)
{
	int				column_width;

	sh->ac->width = sh->window.width;
	sh->ac->height = sh->window.height;
	column_width = sh->ac->len_file_name + 1;
	if (!(sh->ac->number_of_columns = sh->ac->width / column_width))
		sh->ac->number_of_columns = 1;
}
