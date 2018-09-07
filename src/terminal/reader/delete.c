/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:32:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/07 16:09:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_read_delete(t_shell *shell)
{
	unsigned int	i;
	unsigned char	size;

	sh_debug(shell, "before deletion");
	if (shell->term->cursor.abs_pos == 0)
		return ;
	sh_move_left(shell);
	ft_putstr(tgetstr("dc", NULL));
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
	while (--size)
		shell->read->buffer.content[i] = '\0';
	sh_debug(shell, "after deletion");
}
