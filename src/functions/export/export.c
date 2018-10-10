/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:08:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/10 14:21:46 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** implementation
** 		if (no arg) : call env (+ add local var ?)
**		if (arg format "x")
**			check if key corresponds to a local variable
**				local variable : call setenv
**				!local var: add key with empty value
**		OPTIONS ??
*/

char		sh_export(t_shell *sh, char **argv)
{
	int		i;
	char	res;

	res = 0;
	if (!argv || !argv[0])
		return (sh_export_display(sh, false));
	if (ft_strcmps(argv[0], "-p") == 0)
		return (sh_export_display(sh, true));
	i = (ft_strcmps(argv[0], "--") == 0) ? 1 : 0;
	if (i == 0 && argv[0][0] == '-' && !is_option_string(argv[0], "p"))
		return (sh_export_error(NULL, NULL, 1, &argv[0][0]));
	while (argv[i] && (res = sh_export_add(sh, sh->env, argv[i])) == 0)
		i++;
	return (res);
}
