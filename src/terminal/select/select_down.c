/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_down.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 16:02:37 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/25 16:07:53 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_select_down(t_shell *sh)
{
	int		cursor;

	cursor = sh->cursor.abs_pos + sh->window.width;
	if (sh->cursor.abs_pos + sh->window.width > sh->buffer.display_len)
		return (sh_select_end(sh));
	while (sh->cursor.abs_pos != cursor)
		sh_select_right_char(sh);
}
