/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:32:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/05 21:42:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_read_delete(t_shell *shell)
{
	int	i;

	i = -1;
	if (shell->term->cursor.absolute_position == 0)
		return ;
	if (shell->term->cursor.relative_position == 0)
	{
		ft_putstr(tgoto(tgetstr("up", NULL), 0, 0));
		while (++i < shell->term->w_width)
			ft_putstr(tgoto(tgetstr("nd", NULL), 0, 0));
		shell->term->cursor.relative_position = shell->term->w_width;
	}
	else
	{
		ft_putstr(tgoto(tgetstr("le", NULL), 0, 0));
		shell->term->cursor.relative_position--;
	}
	ft_putstr(tgetstr("dc", NULL));
	shell->term->cursor.absolute_position--;
	shell->read->buffer.length--;
}
