/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_to_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:34:51 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 23:36:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void					sh_delete_to_end(t_shell *sh)
{
	int	i;

	i = sh->cursor.rel_pos;
	while (sh->buffer.content[i])
	{
		sh->buffer.content[i] = '\0';
		i++;
	}
	sh->buffer.display_len = ft_strlenu(sh->buffer.content);
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content);
	sh_move_home(sh);
	ft_putstr(K_DEL_ALL);
	ft_putstr(sh->buffer.content);
	sh->cursor.y = (sh->buffer.display_len + sh->prompt.len_mod)
		/ sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->buffer.display_len + sh->prompt.len_mod) % sh->window.width
		: sh->buffer.display_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.rel_pos = sh->buffer.unicode_len;
}
