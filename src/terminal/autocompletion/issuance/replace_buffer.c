/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 14:43:47 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/20 22:40:14 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_add_char(t_shell *sh, char c)
{
	sh->read->buffer.content[sh->read->buffer.unicode_len] = c;
	sh->read->buffer.display_len++;
	sh->read->buffer.unicode_len++;
}

static void	sh_add_wchar(t_shell *sh, unsigned char c)
{
	static char	pointer = 0;
	static char	counter = 0;

	sh->read->buffer.content[sh->read->buffer.unicode_len] = c;
	sh->read->buffer.display_len += (c >= 0b11000000) ? 1 : 0;
	sh->read->buffer.unicode_len++;
	pointer = (c >= 0b11000000) ? 1 : pointer;
	pointer = (c >= 0b11100000) ? 2 : pointer;
	pointer = (c >= 0b11110000) ? 3 : pointer;
	counter = (c < 0b11000000) ? counter - 1 : pointer;
}

void		sh_replace_buffer(t_shell *sh, char *str)
{
	ft_bzero(sh->read->buffer.content, sh->read->buffer.unicode_len);
	sh->read->buffer.display_len = 0;
	sh->read->buffer.unicode_len = 0;
	while (*str)
	{
		if ((unsigned char)*str < 0b10000000 && ft_isprint(*str))
			sh_add_char(sh, *str);
		else if ((unsigned char)*str >= 0b10000000)
			sh_add_wchar(sh, (unsigned char)*str);
		str++;
	}
}
