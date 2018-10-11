/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:13:15 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 14:48:36 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** unalias behavior is like comparable to unset behavior,
** but with aliases.
**
** -----------------------------------------------------------------------------
**
** Syntax
**       unalias name [...]
*/

char			sh_unalias(t_shell *sh, t_env *env, char **argv)
{
	int		i;
	char	res;
	size_t	argc;

	i = 0;
	res = 0;
	argc = ft_count_argv((void **)argv);
	(void)env;
	if (argc == 0)
		return (sh_unalias_error(NULL, 1));
	while (argv[i] && (res = sh_unalias_remove(sh->alias, argv[i])) == 0)
		i++;
	return (res);
}
