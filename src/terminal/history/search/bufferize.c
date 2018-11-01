/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:51:22 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 13:21:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_history_del_char(t_shell *sh)
{
	if (sh->search.len == 0)
		return ;
	sh->search.content[sh->search.len - 1] = '\0';
	sh->search.len--;
}

void		sh_history_bufferize(t_shell *sh, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 127)
			sh_history_del_char(sh);
		else if (sh->search.len + sh->buffer.ushift < ARG_MAX
		&& (((unsigned char)line[i] < 0b10000000 && ft_isprint(line[i]))
		|| (unsigned char)line[i] >= 0b10000000))
		{
			sh->search.content[sh->search.len] = line[i];
			sh->search.len++;
		}
		i++;
	}
}
