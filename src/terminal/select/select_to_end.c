/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_to_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 16:55:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 16:56:19 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_select_end(t_shell *sh)
{
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	while (sh->cursor.abs_pos < sh->buffer.display_len)
		sh_select_right_char(sh);
}
