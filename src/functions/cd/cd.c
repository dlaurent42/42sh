/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:20:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/01 11:56:20 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
**	OPTIONS
**		option -L : Force symbolic links to be followed (default behavior)
**		option -P : Use the physical directory structure without following
**					symbolic links
**
**	EXAMPLES
**		cd link -> repo => link
**		cd -L link -> repo => link
**		cd -P link -> repo => repo
**		cd -L -P link -> repo => repo
**
**	ERRORS
**		if link name equal to itself -> too many levels of symbolic links
**		if link/repo does not exist -> no such file or directory
*/

/*
** add permissions: access denied
*/

char		sh_cd(t_shell *sh, char *value, char **options)
{
	int		option_p;

	option_p = sh_cd_parse_options(options);
	if (!value)
		return (-1);
	if (value[0] == '-' && value[1] == '-' && !value[2])
		return (sh_cd_nofollow(sh, env_search(sh->env, "HOME"), NULL));
	else if (option_p && value[0] == '-' && !value[1])
		return (sh_cd_nofollow(sh, env_search(sh->env, "OLDPWD"), NULL));
	else if (option_p)
		return (sh_cd_nofollow(sh, value, NULL));
	else if (value[0] == '-' && !value[1])
		return (sh_cd_follow(sh, env_search(sh->env, "OLDPWD")));
	else
		return (sh_cd_follow(sh, value));
}
