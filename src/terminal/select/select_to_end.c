/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_to_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 16:55:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 12:00:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_select_end(t_shell *sh)
{
	int		i;

	i = 0;
	if (sh->cursor.abs_pos >= sh->buffer.display_len)
		return ;
	while (sh->buffer.content[i])
	{
		sh->buffer.content[i] = '\0';
		i++;
	}
	ft_putstr(CLEAR_TO_EOL);
}
