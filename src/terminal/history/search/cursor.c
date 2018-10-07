/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:41:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 19:00:19 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_history_move_cursor(t_shell *sh)
{
	int	x;
	int	y;

	y = (sh->prompt.len_mod + sh->buffer.display_len) / sh->window.width;
	y += ((sh->prompt.len_mod + sh->buffer.display_len) % sh->window.width)
		? 1 : 0;
	y = y + (sh->search.old_len + SEARCH_LEN + 1) / sh->window.width;
	x = (sh->search.old_len + SEARCH_LEN + 1) % sh->window.width;
	while (y)
	{
		ft_putstr(K_UP);
		y--;
	}
	while (x)
	{
		ft_putstr(K_LEFT);
		x--;
	}
}
