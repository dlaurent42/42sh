/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 14:43:47 by dhojt             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/09/24 00:19:56 by dhojt            ###   ########.fr       */
=======
/*   Updated: 2018/09/20 22:40:14 by dhojt            ###   ########.fr       */
>>>>>>> d775b7104264c575618a8c5391da8fe9646b8ca2
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_add_char(t_shell *sh, char c)
{
<<<<<<< HEAD
	sh->buffer.content[sh->buffer.unicode_len] = c;
	sh->buffer.display_len++;
	sh->buffer.unicode_len++;
=======
	sh->read->buffer.content[sh->read->buffer.unicode_len] = c;
	sh->read->buffer.display_len++;
	sh->read->buffer.unicode_len++;
>>>>>>> d775b7104264c575618a8c5391da8fe9646b8ca2
}

static void	sh_add_wchar(t_shell *sh, unsigned char c)
{
	static char	pointer = 0;
	static char	counter = 0;

<<<<<<< HEAD
	sh->buffer.content[sh->buffer.unicode_len] = c;
	sh->buffer.display_len += (c >= 0b11000000) ? 1 : 0;
	sh->buffer.unicode_len++;
=======
	sh->read->buffer.content[sh->read->buffer.unicode_len] = c;
	sh->read->buffer.display_len += (c >= 0b11000000) ? 1 : 0;
	sh->read->buffer.unicode_len++;
>>>>>>> d775b7104264c575618a8c5391da8fe9646b8ca2
	pointer = (c >= 0b11000000) ? 1 : pointer;
	pointer = (c >= 0b11100000) ? 2 : pointer;
	pointer = (c >= 0b11110000) ? 3 : pointer;
	counter = (c < 0b11000000) ? counter - 1 : pointer;
}

void		sh_replace_buffer(t_shell *sh, char *str)
{
<<<<<<< HEAD
	ft_bzero(sh->buffer.content, sh->buffer.unicode_len);
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
=======
	ft_bzero(sh->read->buffer.content, sh->read->buffer.unicode_len);
	sh->read->buffer.display_len = 0;
	sh->read->buffer.unicode_len = 0;
>>>>>>> d775b7104264c575618a8c5391da8fe9646b8ca2
	while (*str)
	{
		if ((unsigned char)*str < 0b10000000 && ft_isprint(*str))
			sh_add_char(sh, *str);
		else if ((unsigned char)*str >= 0b10000000)
			sh_add_wchar(sh, (unsigned char)*str);
		str++;
	}
}
