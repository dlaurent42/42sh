/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:13:15 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 14:47:54 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Remove variable or function names
**
** -----------------------------------------------------------------------------
**
** Syntax
**       unset [-fv] [name]
**
** Options : NOT IMPLEMENTED (no function, only variables)
**      -f    The names refer to shell Functions,
**            and the function definition is removed.
**            Readonly variables and functions can not be unset.
**
**      -v    Each name refers to a shell Variable (default)
*/

char			sh_unset(t_shell *sh, t_env *env, char **argv)
{
	int		i;
	char	res;
	size_t	argc;

	i = 0;
	res = 0;
	argc = ft_count_argv((void **)argv);
	(void)sh;
	if (argc == 0)
		return (sh_unset_error(NULL, 1));
	while (argv[i] && (res = sh_unset_remove(env, argv[i])) == 0)
		i++;
	return (res);
}
