/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 04:38:29 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 19:14:50 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_copy_selection(t_shell *sh)
{
	if (!sh->modes.select)
		return ;
	(sh->selection.content) ? ft_strdel(&sh->selection.content) : 0;
	sh->selection.content = ft_strsub(
		sh->buffer.content + sh->buffer.ushift,
		sh->selection.start_rel,
		sh_get_selection_len(sh));
	sh_unselect(sh);
}
