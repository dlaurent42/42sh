/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 16:19:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 16:48:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_search_init(t_shell *sh)
{
	sh_move_end(sh);
	sh_browse_freeze(sh);
	sh->modes.search = TRUE;
	ft_strcpy(sh->buffer.stored, sh->buffer.content + sh->buffer.ushift);
	ft_putstr(SEARCH_PROMPT);
	ft_putchar('_');
	ft_putstr(CURSOR_HIDE);
}
