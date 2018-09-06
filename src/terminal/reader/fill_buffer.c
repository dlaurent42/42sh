/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:47:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/05 22:38:32 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_fill_buffer(t_shell *shell)
{
	unsigned char	i;

	i = 0;
	while (shell->read->line[i])
	{
		if (shell->read->line[i] == 10)
			sh_command_run(shell);
		else
		{
			shell->read->buffer.content[shell->term->cursor.absolute_position] = shell->read->line[i];
			shell->read->buffer.length++;
			shell->term->cursor.absolute_position++;
			shell->term->cursor.relative_position =
			(shell->term->cursor.relative_position == shell->term->w_width)
			? 0 : shell->term->cursor.relative_position + 1;
			ft_printf("%s%c%s", tgetstr("im", NULL), shell->read->line[i], tgetstr("ei", NULL));
		}
		i++;
	}
}
