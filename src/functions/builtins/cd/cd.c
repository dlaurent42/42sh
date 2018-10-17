/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:20:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 11:11:35 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Change Directory - change the current working directory to a specific Folder.
**
** -----------------------------------------------------------------------------
**
** Syntax
** 		cd [-L|[-P [-e]] [-@] [directory]
**
** Source
** 		https://www.gnu.org/software/bash/manual/html_node/
**			Bourne-Shell-Builtins.html#Bourne-Shell-Builtins
*/

static char	sh_cd_check_result(bool e, bool p, char res)
{
	char	*path;

	path = NULL;
	if (!e || !p || res != 0)
		return (res);
	if (!(path = getcwd(path, PATH_MAX)))
		return (1);
	ft_strdel(&path);
	return (res);
}

char		sh_cd(t_shell *sh, t_env *env, char **argv)
{
	int		current;
	bool	option_e;
	bool	option_l;
	bool	option_p;
	size_t	argc;

	current = 0;
	option_e = FALSE;
	option_l = FALSE;
	option_p = FALSE;
	argc = ft_count_argv((void **)argv);
	current = sh_cd_options(argv, &option_e, &option_l, &option_p);
	if (ft_count_argv((void **)argv + current) > 1)
		return (sh_cd_error(argv[current], NULL, 4));
	current = (option_p)
		? sh_cd_dispatch_p(sh, env, argv, current)
		: sh_cd_dispatch(sh, env, argv, current);
	return (sh_cd_check_result(option_e, option_p, current));
}
