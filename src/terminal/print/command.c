/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:32:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/04 19:13:26 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_print_cmd(t_shell *sh, t_cmd *cmd)
{
	sh->buffer.cmd = cmd;
	sh_delete_all(sh);
	ft_strcpy(sh->buffer.content + sh->buffer.ushift, cmd->content);
	ft_putstr(sh->buffer.content + sh->buffer.ushift);
	sh->buffer.unicode_len = cmd->unicode_len;
	sh->buffer.display_len = cmd->display_len;
	sh->cursor.abs_pos = sh->buffer.display_len;
	sh->cursor.rel_pos = sh->buffer.unicode_len;
	sh->cursor.y = (sh->buffer.display_len + sh->prompt.len_mod)
	/ sh->window.width;
	sh->cursor.x = (sh->cursor.y)
		? (sh->buffer.display_len + sh->prompt.len_mod) % sh->window.width
		: sh->buffer.display_len;
	sh->modes.browse = TRUE;
}
