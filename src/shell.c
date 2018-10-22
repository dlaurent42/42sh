/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/22 16:46:53 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	debug_globbing(char *argument)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdups(argument);
	ft_printf("Received argument: %s\n", str);
	str = sh_glob(str);
	ft_printf("Returned argument: ");
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	ft_printf("\n");
	ft_strdel(&str);
	return (EXIT_SUCCESS);
}

int			main(int argc, char **argv, char **environ)
{
	t_shell		*sh;

	sh = NULL;
	if (argc > 1)
		return (debug_globbing(argv[1]));
	sh = sh_new(environ);
	sh_welcome();
	signal_catching();
	sh_read(sh);
	sh_delete(sh);
	return (EXIT_SUCCESS);
}
