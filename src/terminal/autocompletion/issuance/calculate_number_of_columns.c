/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_number_of_columns.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 13:29:46 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 08:43:52 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

void				auto_calculate_number_of_columns(t_shell *sh)
{
	int				column_width;

	sh->ac->width = sh->window.width;
	sh->ac->height = sh->window.height;
	column_width = sh->ac->len_file_name + 1;
	if(!(sh->ac->number_of_columns = sh->ac->width / column_width))
		sh->ac->number_of_columns = 1;
}
