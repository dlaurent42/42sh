/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_to_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 16:53:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 16:55:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_select_home(t_shell *sh)
{
	if (sh->cursor.abs_pos == 0)
		return ;
	while (sh->cursor.abs_pos)
		sh_select_left_char(sh);
}
