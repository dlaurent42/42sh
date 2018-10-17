/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:42:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 20:11:32 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Create an alias, aliases allow a string to be substituted for a word when it
** is used as the first word of a simple command.
**
** -----------------------------------------------------------------------------
**
** Syntax
**       alias [-p] [name[=value] ...]
**
** Options
**
**    -p   Print the current values
**
** If arguments are supplied, an alias is defined for each name whose value
** is given.
**
** If no value is given, alias will print the current value of the alias.
**
** Without arguments or with the -p option, alias prints the list of aliases
** on the standard output in a form that allows them to be reused as input.
**
** The value cannot contain any positional parameters ($1 etc), if you need to
** do that use a shell function instead.
*/

char		sh_alias(t_shell *sh, t_env *env, char **argv)
{
	int		i;
	char	res;

	res = 0;
	(void)env;
	if (!argv || !argv[0])
		return (env_display(sh->alias, ""));
	if (ft_strcmps(argv[0], "-p") == 0)
		return (env_display(sh->alias, "alias "));
	i = (ft_strcmps(argv[0], "--") == 0) ? 1 : 0;
	if (i == 0 && argv[0][0] == '-' && !sh_is_option_string(argv[0], "p"))
		return (sh_alias_error(NULL, NULL, 1, &argv[0][0]));
	while (argv[i] && (res = sh_alias_add(sh, sh->alias, argv[i])) == 0)
		i++;
	return (res);
}
