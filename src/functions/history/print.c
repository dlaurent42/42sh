/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 15:05:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/08 17:41:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_history_print(t_shell *sh)
{
	int		len;
	t_cmd	*cmd;

	if (!(cmd = sh->cmd))
		return (0);
	len = str_size_base(10, cmd->id);
	cmd = cmd->last;
	while (cmd)
	{
		ft_printf("%*d\t%s\n", len, cmd->id, cmd->content);
		cmd = cmd->next;
	}
	return (0);
}

char	sh_history_print_shift(t_shell *sh, int shift)
{
	int		len;
	t_cmd	*cmd;

	if (!(cmd = sh->cmd))
		return (0);
	len = str_size_base(10, cmd->id);
	while (cmd->prev && cmd->id > sh->cmd->id - shift)
		cmd = cmd->prev;
	while (cmd)
	{
		ft_printf("%*d\t%s\n", len, cmd->id, cmd->content);
		cmd = cmd->next;
	}
	return (0);
}
