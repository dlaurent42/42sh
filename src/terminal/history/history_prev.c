/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_prev.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 22:06:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 22:14:06 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_browse_prev(t_shell *sh)
{
	t_cmd	*cmd;

	if (!sh->modes.browse)
		return ;
	if (!(cmd = sh->buffer.cmd->prev))
		return ;
	while (cmd && ft_strcmps(cmd->cmd, sh->buffer.content) <= 0)
		cmd = cmd->prev;
	(cmd) ? sh->buffer.cmd = cmd : 0;
}
