/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 18:42:36 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			main(int argc, char **argv, char **environ)
{
	t_shell		*sh;

	(void)argc;
	(void)argv;
	sh = NULL;
	sh = sh_new(environ);
	sh_welcome();
	signal_catching();
	sh_read(sh);
	sh_delete(sh);
	return (EXIT_SUCCESS);
}
