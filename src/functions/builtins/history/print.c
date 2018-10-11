/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 15:05:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 21:35:26 by dlaurent         ###   ########.fr       */
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
		(cmd->is_new)
			? ft_printf("%*d* %s\n", len, cmd->id, cmd->content)
			: ft_printf("%*d  %s\n", len, cmd->id, cmd->content);
		cmd = cmd->prev;
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
	while (cmd->next && --shift)
		cmd = cmd->next;
	while (cmd)
	{
		(cmd->is_new)
			? ft_printf("%*d* %s\n", len, cmd->id, cmd->content)
			: ft_printf("%*d  %s\n", len, cmd->id, cmd->content);
		cmd = cmd->prev;
	}
	return (0);
}
