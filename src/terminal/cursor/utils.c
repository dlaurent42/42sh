/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 19:05:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 20:42:45 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_set_rel_pos(t_shell *sh, int delta, int dir)
{
	unsigned char	c;

	while (delta > 0)
	{
		sh->cursor.rel_pos += dir;
		c = (unsigned char)sh->buffer.content[sh->buffer.ushift
		+ sh->cursor.rel_pos];
		if (c < 0b10000000 || c >= 0b11000000)
			delta--;
	}
}
