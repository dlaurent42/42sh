/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 04:38:29 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/21 04:51:30 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_get_selection_len(t_shell *sh)
{
	int	len;
	int	index;

	len = 0;
	index = sh->selection.start_rel;
	while (index < sh->selection.stop)
	{
		len += ((unsigned char)sh->buffer.content[index] >= 0b11110000) ? 1 : 0;
		len += ((unsigned char)sh->buffer.content[index] >= 0b11100000) ? 1 : 0;
		len += ((unsigned char)sh->buffer.content[index] >= 0b11000000) ? 1 : 0;
		len += ((unsigned char)sh->buffer.content[index] < 0b10000000) ? 1 : 0;
		index++;
	}
	return (len);
}

void		sh_copy_selection(t_shell *sh)
{
	(void)sh;
	if (!sh->modes.select)
		return ;
	sh_debug(
		NULL,
		ft_strsub(
			sh->buffer.content,
			sh->selection.start_rel,
			sh_get_selection_len(sh)),
		NULL);
	sh_unselect(sh);
}
