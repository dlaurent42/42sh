/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_buffer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:27:35 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 07:04:15 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
# include "auto_completion.h"
# include "auto_completion_prot.h"

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
