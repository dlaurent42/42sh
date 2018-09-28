/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 14:32:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/28 15:25:28 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_print_cmd(t_shell *sh, t_cmd *cmd)
{
	sh->buffer.cmd = cmd;
	sh_delete_all(sh);
	sh_print_str(sh, cmd->content);
	sh->modes.browse = TRUE;
}
