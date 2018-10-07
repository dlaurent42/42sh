/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:29:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 17:30:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_delete_all(t_shell *sh)
{
	int	i;

	i = 0;
	if ((sh->buffer.display_len + sh->prompt.len)
	/ sh->window.width + 1 > sh->window.height)
	{
		sh_move_home(sh);
		ft_putstr(CLEAR_SCREEN);
		sh_print_prompt(sh);
		sh->cursor.abs_pos = 0;
		sh->cursor.rel_pos = 0;
		sh->cursor.x = 0;
		sh->cursor.y = 0;
	}
	else
	{
		sh_move_home(sh);
		ft_putstr(K_DEL_ALL);
	}
	bzero(sh->buffer.content + sh->buffer.ushift, sh->buffer.unicode_len);
	sh->buffer.unicode_len = 0;
	sh->buffer.display_len = 0;
}
