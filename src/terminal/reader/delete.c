/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:32:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/14 16:59:44 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	sh_move_cursor(t_shell *shell)
// {
// 	unsigned int	x;
// 	unsigned int	y;
// 	unsigned int	buffer_len;
// 	unsigned int	header_len;
// 	unsigned int	window_width;

// 	sh_debug(shell, "avant merde");
// 	x = shell->term->cursor.x;
// 	y = shell->term->cursor.y;
// 	buffer_len = shell->read->buffer.display_length + 1;
// 	header_len = shell->term->header.display_length_mod;
// 	window_width = shell->term->window.width;
// 	shell->term->cursor.y = (buffer_len + header_len) / window_width;
// 	shell->term->cursor.x = (shell->term->cursor.y)
// 		? (buffer_len + header_len) % window_width
// 		: buffer_len;
// 	sh_debug(shell, "avant xy");
// 	if ((y == 0 && x + 2 + header_len > window_width) || (y > 0 && x + 2 > window_width))
// 		sh_move_to_xy(shell, 0, y + 1);
// 	else
// 		sh_move_to_xy(shell, x + 1, y);
// }

static void		sh_perform_deletion(t_shell *shell)
{
	unsigned int	i;
	int				size;

	i = shell->term->cursor.rel_pos;
	size = 1;
	while (shell->read->buffer.content[i + size] >= 0b10000000
	&& shell->read->buffer.content[i + size] < 0b11000000)
		size++;
	shell->read->buffer.display_length--;
	shell->read->buffer.unicode_length -= size;
	while (shell->read->buffer.content[i + size])
	{
		shell->read->buffer.content[i] = shell->read->buffer.content[i + size];
		i++;
	}
	while (--size >= 0)
		shell->read->buffer.content[i + size] = '\0';
}

void			sh_read_delete(t_shell *shell)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	display_length;

	if (shell->term->cursor.abs_pos == 0)
		return ;
	sh_debug(shell, "before all");
	display_length = shell->read->buffer.display_length;
	sh_move_left(shell);
	sh_perform_deletion(shell);
	ft_putstr(K_DEL);
	ft_putstr(K_LEFT);
	ft_printf("%s",
		shell->read->buffer.content
		+ shell->term->cursor.rel_pos);
	x = shell->term->cursor.x;
	y = shell->term->cursor.y;
	shell->term->cursor.rel_pos = shell->read->buffer.unicode_length + display_length;
	shell->term->cursor.abs_pos = shell->read->buffer.display_length + display_length;
	shell->term->cursor.y = (shell->read->buffer.display_length + shell->term->header.display_length_mod) / shell->term->window.width;
	shell->term->cursor.x = (shell->term->cursor.y)
		? (shell->read->buffer.display_length + shell->term->header.display_length_mod) % shell->term->window.width
		: shell->read->buffer.display_length;
	while (display_length != shell->read->buffer.display_length)
	{
		ft_putchar(' ');
		display_length--;
	}
	sh_debug(shell, "del pos");
	sh_debug(NULL, ft_itoa(x));
	sh_debug(NULL, ft_itoa(y));
}
