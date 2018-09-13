/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/12 15:44:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_set_rel_pos(t_shell *shell, unsigned int delta, int dir)
{
	unsigned char	c;

	while (delta > 0)
	{
		shell->term->cursor.rel_pos += dir;	
		c = shell->read->buffer.content[shell->term->cursor.rel_pos];
		if (c < 0b10000000 || c >= 0b11000000)
			delta--;
	}
}
