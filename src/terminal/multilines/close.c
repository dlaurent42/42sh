/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 20:31:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/02 18:29:46 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_multilines_close(t_shell *sh)
{
	bool	subshell;

	subshell = sh->modes.subshell;
	sh_move_end(sh);
	ft_bzero(sh->buffer.content, sh->buffer.unicode_len + sh->buffer.ushift);
	sh->buffer.display_len = 0;
	sh->buffer.unicode_len = 0;
	sh->buffer.dshift = 0;
	sh->buffer.ushift = 0;
	sh->buffer.cmd = NULL;
	sh->read->unicode_bytes_left = 0;
	ft_bzero((void *)&sh->cursor, sizeof(t_cursor));
	ft_bzero((void *)&sh->modes, sizeof(t_modes));
	(!subshell) ? ft_putchar('\n') : 0;
	if (env_search(sh->env, "?") || sh->env->count + 1 < sh->env->size)
		env_insert_protected(sh, sh->env, "?", "0");
	(!subshell) ? sh_set_prompt(sh) : 0;
	(!subshell) ? sh_print_prompt(sh) : 0;
	sh->modes.subshell = (subshell) ? 2 : 0;
}
