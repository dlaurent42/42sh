/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_acquisition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:16:07 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/02 15:55:54 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_sigint_reset(t_shell *sh, char *last_return)
{
	bool	subshell;

	if (!sh)
		return ;
	subshell = sh->modes.subshell;
	sh_move_end(sh);
	ft_putchar('\n');
	ft_bzero(sh->buffer.content, sh->buffer.unicode_len + sh->buffer.ushift);
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
	sh->buffer.dshift = 0;
	sh->buffer.ushift = 0;
	sh->buffer.cmd = NULL;
	(sh->read) ? sh->read->unicode_bytes_left = 0 : 0;
	sh->pid = 0;
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	ft_bzero((void *)&sh->modes, sizeof(t_modes));
	if (sh->env
	&& (env_search(sh->env, "?") || sh->env->count + 1 < sh->env->size))
		env_insert_protected(sh, sh->env, "?", last_return);
	(sh && !subshell) ? sh_set_prompt(sh) : 0;
	(sh && !subshell) ? sh_print_prompt(sh) : 0;
	ft_putstr(CURSOR_SHOW);
}
