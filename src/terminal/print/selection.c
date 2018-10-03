/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 03:47:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 21:53:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_select_print(t_shell *sh)
{
	int	i;
	int	len;

	i = 0;
	len = sh_get_selection_len(sh);
	ft_putstr("\e[7;37;40m");
	while (sh->buffer.content[sh->cursor.rel_pos + i])
	{
		if (sh->cursor.rel_pos + i >= sh->selection.start_rel
		&& sh->cursor.rel_pos + i < sh->selection.start_rel + len)
			ft_printf("%c", sh->buffer.content[sh->cursor.rel_pos + i]);
		else
		{
			ft_printf("\033[0m%s ",
				sh->buffer.content + sh->cursor.rel_pos + i);
			break ;
		}
		i++;
	}
	(sh->cursor.rel_pos + i >= sh->selection.stop) ? ft_putstr("\033[0m") : 0;
	sh_select_set_pos(sh);
}
