/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 01:11:14 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 14:48:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** setenv behavior is like comparable to export behavior,
** except it not possible to communicate with local variables.
**
** -> setenv add non-local variables to env
**
** -----------------------------------------------------------------------------
**
** Syntax
**       setenv name=value [...]
*/

char		sh_setenv(t_shell *sh, t_env *env, char **argv)
{
	int		i;
	char	res;
	size_t	argc;

	i = 0;
	res = 0;
	argc = ft_count_argv((void **)argv);
	if (argc == 0)
		return (sh_setenv_error(NULL, NULL, 1));
	while (argv[i] && (res = sh_setenv_add(sh, env, argv[i])) == 0)
		i++;
	return (res);
}
