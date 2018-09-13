/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:32:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/13 18:17:50 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_putstr((char *)(shell->read->buffer.content + shell->term->cursor.rel_pos));
	while (display_length != shell->read->buffer.display_length)
	{
		ft_putchar(' ');
		display_length--;
	}
	sh_move_to_xy(shell, shell->term->cursor.x, shell->term->cursor.y);
}
