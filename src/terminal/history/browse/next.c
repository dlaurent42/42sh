/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 22:06:28 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 16:14:22 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_reset_history(t_shell *sh)
{
	sh->buffer.cmd = NULL;
	ft_bzero(sh->buffer.content + sh->buffer.ushift, sh->buffer.unicode_len);
	sh_delete_all(sh);
	sh_print_str(sh, sh->buffer.stored);
	ft_bzero(sh->buffer.stored, ARG_MAX + 1);
	sh->modes.browse = FALSE;
}

void		sh_browse_next(t_shell *sh)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	cmd = NULL;
	if (!sh->modes.browse)
		return ;
	tmp = sh->buffer.cmd->prev;
	while (tmp)
	{
		if (sh->buffer.cmd
		&& ft_strcmps(sh->buffer.cmd->content, tmp->content) == 0)
			tmp = tmp->prev;
		else if (sh_browse_compare(tmp->content, sh->buffer.stored) == 0)
		{
			cmd = tmp;
			break ;
		}
		else
			tmp = tmp->prev;
	}
	(cmd) ? sh_print_cmd(sh, cmd) : 0;
	(!tmp) ? sh_reset_history(sh) : 0;
}
