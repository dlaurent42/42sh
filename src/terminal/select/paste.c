/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:51:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/29 19:18:19 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_paste_selection(t_shell *sh)
{
	if (!sh->selection.content)
		return ;
	if (sh->modes.select == TRUE)
		sh_unselect_delete(sh, 22);
	sh_print_str(sh, sh->selection.content);
}
