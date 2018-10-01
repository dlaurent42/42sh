/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_from_home.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 14:34:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 15:24:52 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_delete_from_home(t_shell *sh)
{
	while (sh->cursor.abs_pos)
		sh_delete_char(sh);
}
