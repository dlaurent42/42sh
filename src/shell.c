/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/09/24 00:12:17 by dhojt            ###   ########.fr       */
=======
/*   Updated: 2018/09/23 16:42:04 by dhojt            ###   ########.fr       */
>>>>>>> d775b7104264c575618a8c5391da8fe9646b8ca2
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
	signal_catching();
	auto_completion(sh);
	sh_read(sh);
	sh_delete(sh);
	return (0);
}
