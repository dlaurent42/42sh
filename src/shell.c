/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/20 17:35:01 by dlaurent         ###   ########.fr       */
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
	ft_printf("Initial: [%s]\n", argv[1]);
	char *str = sh_glob(ft_strdups(argv[1]));
	// int	i = 0;
	// ft_printf("Final:", str);
	// while (str[i])
	// {
	// 	ft_printf(" %c", str[i]);
	// 	i++;
	// }
	// ft_printf("]\n");
	int i = 0;
	ft_printf("Final: [");
	while (str[i])
	{
		ft_printf("%c", str[i]);
		i++;
	}
	ft_printf("]\n");
	ft_strdel(&str);
	(void)environ;
	return (0);
}
