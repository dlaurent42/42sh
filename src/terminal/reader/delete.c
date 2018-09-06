/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:32:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/06 13:32:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_read_delete(t_shell *shell)
{
	int	i;

	i = -1;
	if (shell->term->cursor.abs_pos == 0)
		return ;
	sh_move_left(shell);
	ft_putstr(tgetstr("dc", NULL));
	shell->read->buffer.length--;
}
