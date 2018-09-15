/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:32:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/15 22:25:10 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_move_cursor(t_shell *shell, unsigned int displayed_len)
{
	unsigned int	x;
	unsigned int	y;

	x = shell->term->cursor.x;
	y = shell->term->cursor.y;
	shell->term->cursor.rel_pos = shell->read->buffer.unicode_length + displayed_len - shell->read->buffer.display_length;
	shell->term->cursor.abs_pos = shell->read->buffer.display_length + displayed_len - shell->read->buffer.display_length;
	shell->term->cursor.y = (shell->term->cursor.abs_pos + shell->term->prompt.display_length_mod) / shell->term->window.width;
	shell->term->cursor.x = (shell->term->cursor.y)
		? (shell->term->cursor.abs_pos + shell->term->prompt.display_length_mod) % shell->term->window.width
		: shell->term->cursor.abs_pos;
	while (displayed_len != shell->read->buffer.display_length)
	{
		ft_putchar(' ');
		displayed_len--;
	}
	sh_move_to_xy(shell, x, y);
}

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
	unsigned int	display_length;

	if (shell->term->cursor.abs_pos == 0)
		return ;
	display_length = shell->read->buffer.display_length;
	sh_move_left(shell);
	sh_perform_deletion(shell);
	ft_putstr(K_DEL);
	ft_putstr(K_LEFT);
	ft_printf("%s",
		shell->read->buffer.content
		+ shell->term->cursor.rel_pos);
	sh_move_cursor(shell, display_length);
}
