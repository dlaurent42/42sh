/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:08:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 11:21:19 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Set an environment variable. Mark each name to be passed to child processes
** in the environment.
**
** -----------------------------------------------------------------------------
**
** Syntax
**       export [-fn] [-p] [name[=value]]
**
** Options
**       -p   Display output in a form that can be reused as input.
**
** If no names are supplied, or if the `-p' option is given, a list of exported
** names is displayed.
*/

char		sh_export(t_shell *sh, t_env *env, char **argv)
{
	int		i;
	char	res;

	res = 0;
	if (!argv || !argv[0])
		return (env_display(env, ""));
	if (ft_strcmps(argv[0], "-p") == 0)
		return (env_display(env, "export "));
	i = (ft_strcmps(argv[0], "--") == 0) ? 1 : 0;
	if (i == 0 && argv[0][0] == '-' && !sh_is_option_string(argv[0], "p"))
		return (sh_export_error(NULL, NULL, 1, &argv[0][0]));
	while (argv[i] && (res = sh_export_add(sh, env, argv[i])) == 0)
		i++;
	return (res);
}
