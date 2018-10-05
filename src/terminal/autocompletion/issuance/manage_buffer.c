/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:27:35 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/05 13:24:13 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				auto_manage_buffer(t_shell *sh, char *new_display_str)
{
	while (*new_display_str)
	{
		sh->read->line[0] = *new_display_str;
		sh_fill_buffer(sh);
		new_display_str++;
	}
	ft_bzero(sh->read->line, LINE_SIZE);
}
