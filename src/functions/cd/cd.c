/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:20:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/29 00:37:38 by dlaurent         ###   ########.fr       */
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
	if (!value)
		return (-1);
	if (sh_cd_parse_options(options))
		return (sh_cd_nofollow(sh, value, NULL));
	return (sh_cd_follow(sh, value));
}
