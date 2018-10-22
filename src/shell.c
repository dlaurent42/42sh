/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/22 15:01:29 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		main(int argc, char **argv, char **environ)
{
	t_shell		*sh;

	sh = NULL;
	(void)argc;
	// (void)argv;
	// sh = sh_new(environ);
	// sh_welcome();
	// signal_catching();
	// sh_read(sh);
	// sh_delete(sh);
	(void)environ;
	char	*str = ft_strdups(argv[1]);
	ft_printf("initial: %s\n", str);
	str = sh_glob(str);
	int		i = 0;
	ft_printf("final  : [");
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_printf("]\n");
	ft_strdel(&str);
	return (EXIT_SUCCESS);
}
