/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:13:15 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 20:40:07 by dlaurent         ###   ########.fr       */
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
**
** Options
**
**    -a   Delete all aliases
*/

static char		sh_unalias_all(t_shell *sh, t_env *env)
{
	env_delete(env);
	sh->alias = env_new(sh, NULL);
	return (0);
}

char			sh_unalias(t_shell *sh, t_env *env, char **argv)
{
	int		i;
	char	res;
	bool	opt_a;
	size_t	argc;

	(void)env;
	i = -1;
	res = 0;
	opt_a = FALSE;
	argc = ft_count_argv((void **)argv);
	while (argv[++i])
		if (ft_strcmps("--", argv[i]) == 0)
		{
			i++;
			break ;
		}
		else if (ft_strcmps("-a", argv[i]) == 0)
			return (sh_unalias_all(sh, sh->alias));
		else
			break ;
	if (argc - i == 0)
		return (sh_unalias_error(NULL, 1));
	while (argv[i] && (res = sh_unalias_remove(sh->alias, argv[i])) == 0)
		i++;
	return (res);
}
