/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 17:29:03 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 19:06:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_history_print_result(t_shell *sh)
{
	ft_putstr(K_DEL_ALL);
	ft_putstr(sh->prompt.content);
	ft_putstr(sh->buffer.content + sh->buffer.ushift);
	ft_putstr(SEARCH_PROMPT);
	ft_putstr(sh->search.content);
	ft_putchar('_');
	sh->search.len = ft_strlens(sh->search.content);
	sh->search.old_len = sh->search.len;
	sh->buffer.unicode_len = ft_strlens(sh->buffer.content + sh->buffer.ushift);
	sh->buffer.display_len = ft_strlenu(sh->buffer.content + sh->buffer.dshift);
}
