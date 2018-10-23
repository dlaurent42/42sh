/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 00:41:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/23 20:13:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	debug_globbing(t_shell *sh, char *argument)
{
	int		i;
	char	*str;

	i = 0;
	if (!(str = ft_strdups(argument)))
	{
		sh_delete(sh);
		return (EXIT_FAILURE);
	}
	str = (str[0] == '$')
		? sh_dollar_expansion(str, sh->env)
		: sh_glob(str);
	sh_delete(sh);
	ft_printf("Received argument: %s\n", argument);
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
	sh = sh_new(environ);
	if (argc > 1)
		return (debug_globbing(sh, argv[1]));
	sh_welcome();
	signal_catching();
	sh_read(sh);
	sh_delete(sh);
	return (EXIT_SUCCESS);
}
