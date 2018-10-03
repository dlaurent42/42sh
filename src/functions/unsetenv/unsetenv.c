/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 01:11:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 20:12:20 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_unsetenv(t_shell *sh, char **argv)
{
	int		i;
	char	res;
	size_t	argc;

	i = 0;
	res = 0;
	argc = ft_count_argv((void **)argv);
	if (argc == 0)
		return (sh_unsetenv_error(NULL, 1));
	while (argv[i] && (res = sh_unsetenv_remove(sh, argv[i])) == 0)
		i++;
	return (res);
}
