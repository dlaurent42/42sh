/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 19:51:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 12:46:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_paste_selection(t_shell *sh)
{
	if (!sh->selection.content)
		return ;
	sh_print_str(sh, sh->selection.content);
}
