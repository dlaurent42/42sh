/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prev.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 22:06:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 16:14:17 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_browse_prev(t_shell *sh)
{
	t_cmd	*tmp;
	t_cmd	*cmd;

	cmd = NULL;
	(!sh->modes.browse)
		? ft_strcpy(sh->buffer.stored, sh->buffer.content + sh->buffer.ushift)
		: 0;
	tmp = (!sh->modes.browse) ? sh->cmd : sh->buffer.cmd->next;
	while (tmp)
	{
		if (sh->buffer.cmd
		&& ft_strcmps(sh->buffer.cmd->content, tmp->content) == 0)
			tmp = tmp->next;
		else if (sh_browse_compare(tmp->content, sh->buffer.stored) == 0)
		{
			cmd = tmp;
			break ;
		}
		else
			tmp = tmp->next;
	}
	(cmd) ? sh_print_cmd(sh, cmd) : 0;
}
