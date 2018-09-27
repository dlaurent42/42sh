/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/27 17:34:25 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		main(int argc, char **argv, char **environ)
{
	t_shell		*sh;

	sh = NULL;
	(void)argc;
	(void)argv;
	sh = sh_new(environ);
	g_sh = sh;
	if (!sh->cmd)
		sh_debug(NULL, "err", NULL);
	while (sh->cmd)
	{
		sh_debug(NULL, sh->cmd->cmd, NULL);
		sh->cmd = sh->cmd->next;
	}
	sh_welcome();
	signal_catching();
	sh_read(sh);
	sh_delete(sh);
	return (0);
}
