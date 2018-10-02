/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 00:19:57 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/03 00:58:15 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				sh_history(t_shell *sh)
{
	t_cmd			*cmd;
	unsigned int	id;
	int				len;

	if (!sh->cmd)
	{
		ft_putendl("no history to display");
		return ;
	}
	len = 1;
	id = sh->cmd->id;
	while (id > 10)
	{
		id /= 10;
		len++;
	}
	cmd = sh->cmd->last;
	while (cmd)
	{
		ft_printf("%*u: %s\n", len, cmd->id, cmd->content);
		cmd = cmd->prev;
	}
}
