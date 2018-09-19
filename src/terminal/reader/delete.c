/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:32:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/19 21:47:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_move_cursor(t_shell *sh, int displayed_len)
{
	unsigned int	x;
	unsigned int	y;

	x = sh->cursor.x;
	y = sh->cursor.y;
	sh->cursor.rel_pos = sh->read->buffer.unicode_len + displayed_len - sh->read->buffer.display_len;
	sh->cursor.abs_pos = sh->read->buffer.display_len + displayed_len - sh->read->buffer.display_len;
	sh->cursor.y = (sh->cursor.abs_pos + sh->prompt.len_mod) / sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->cursor.abs_pos + sh->prompt.len_mod) % sh->window.width
		: sh->cursor.abs_pos;
	while (displayed_len != sh->read->buffer.display_len)
	{
		ft_putchar(' ');
		displayed_len--;
	}
	sh_move_to_xy(sh, x, y);
}

static void		sh_perform_deletion(t_shell *sh)
{
	int	i;
	int	size;

	i = sh->cursor.rel_pos;
	size = 1;
	while ((unsigned char)sh->read->buffer.content[i + size] >= 0b10000000
	&& (unsigned char)sh->read->buffer.content[i + size] < 0b11000000)
		size++;
	sh->read->buffer.display_len--;
	sh->read->buffer.unicode_len -= size;
	while (sh->read->buffer.content[i + size])
	{
		sh->read->buffer.content[i] = sh->read->buffer.content[i + size];
		i++;
	}
	while (--size >= 0)
		sh->read->buffer.content[i + size] = '\0';
}

void			sh_read_delete(t_shell *sh)
{
	int	display_len;

	if (sh->cursor.abs_pos == 0)
		return ;
	display_len = sh->read->buffer.display_len;
	sh_move_left(sh);
	sh_perform_deletion(sh);
	ft_putstr(K_DEL);
	ft_putstr(K_LEFT);
	ft_printf("%s",
		sh->read->buffer.content
		+ sh->cursor.rel_pos);
	sh_move_cursor(sh, display_len);
}
