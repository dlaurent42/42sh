/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/03 20:36:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			main(int argc, char **argv, char **environ)
{
	int			status;
	t_shell		*sh;

	sh = NULL;
	sh = sh_new(argc, argv, environ);
	(argc == 1) ? sh_welcome() : 0;
	signal_catching();
	status = (argc == 1)
		? sh_read(sh)
		: sh_subshell(sh, argv + 1);
	sh_delete(sh);
	return (status);
}
