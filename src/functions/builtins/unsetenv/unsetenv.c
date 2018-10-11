/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 01:11:39 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 14:48:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** unsetenv behavior is like comparable to unset behavior,
** except it not possible to communicate with local variables.
**
** -> unsetenv remove non-local variables from env
**
** -----------------------------------------------------------------------------
**
** Syntax
**       unset name [...]
*/

char	sh_unsetenv(t_shell *sh, t_env *env, char **argv)
{
	int		i;
	char	res;
	size_t	argc;

	i = 0;
	res = 0;
	argc = ft_count_argv((void **)argv);
	(void)sh;
	if (argc == 0)
		return (sh_unsetenv_error(NULL, 1));
	while (argv[i] && (res = sh_unsetenv_remove(env, argv[i])) == 0)
		i++;
	return (res);
}
