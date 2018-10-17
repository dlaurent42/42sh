/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 01:11:14 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 22:28:55 by dlaurent         ###   ########.fr       */
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

	res = 0;
	if (!argv || !argv[0])
		return (env_display(env, ""));
	if (ft_strcmps(argv[0], "-p") == 0)
		return (env_display(env, "setenv "));
	i = (ft_strcmps(argv[0], "--") == 0) ? 1 : 0;
	if (i == 0 && argv[0][0] == '-' && !sh_is_option_string(argv[0], "p"))
		return (sh_export_error(NULL, NULL, 1, &argv[0][0]));
	while (argv[i] && (res = sh_setenv_add(sh, env, argv[i])) == 0)
		i++;
	return (res);
}
