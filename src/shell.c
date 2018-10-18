/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 22:24:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		main(int argc, char **argv, char **environ)
{
	t_shell		*sh;

	sh = NULL;
	(void)argc;
//	(void)argv;
	sh = sh_new(environ);
//	sh_welcome();
//	signal_catching();
//	sh_read(sh);

	int i = 0;
	while (argv[++i])
		sh_glob(argv[i]);
	sh_delete(sh);
	return (0);
}
