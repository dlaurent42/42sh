/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:29:01 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 15:24:38 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_delete_all(t_shell *sh)
{
	sh_move_end(sh);
	while (sh->cursor.abs_pos)
		sh_delete_char(sh);
}
