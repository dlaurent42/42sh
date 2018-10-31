/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:51:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/31 10:39:51 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	SOURCES
** 		http://manpages.ubuntu.com/manpages/xenial/en/man7/glob.7.html
** 		http://tldp.org/LDP/abs/html/globbingref.html
**
**	PATTERNS
**
**		By default, globbing does not take into account hidden files and folders
**		To look for those, user must specify . (i.e.: `.*`)
**
**		*	Wildcard can match multiple characters
**		?	Interrogation mark can match one character
**		[]	Ranges match all patterns
**			[ab]	can match a or b
**			[a-d]	can match a, b, c or d
**			[!a-d]	cannot match a, b, c or d
**		{}	Curly braces
**			{1..9}	   -> 1 2 3 4 5 6 7 8 9
**			{a,b}	   -> a b
**			{{A,b}..2} -> \{A..2\} \{b..2\}
**			{{A..b},2} -> A B C D E F G H I J K L M NO P Q R S T U V W X Y
**						  Z \[ \\ \] \^ _ \` a b 2
**			{{A,b},c} -> A b c
*/

#include "shell.h"

char	*sh_glob(char *str)
{
	int		i;
	char	*cbraces;
	char	*expansion;
	char	**cbracessplit;

	i = 0;
	if (!str || !str[0])
		return (str);
	g_sh->modes.globbing = TRUE;
	expansion = NULL;
	cbraces = sh_glob_cbraces(str);
	cbracessplit = cbraces_strsplit(cbraces, ' ');
	while (cbracessplit && cbracessplit[i])
	{
		(expansion) ? expansion = ft_strjoinf(expansion, " ", 1) : 0;
		expansion = ft_strjoinf(expansion, sh_glob_pattern(cbracessplit[i]), 3);
		ft_strdel(&cbracessplit[i]);
		i++;
	}
	(cbracessplit) ? free(cbracessplit) : 0;
	g_sh->modes.globbing = FALSE;
	if (!expansion)
		return (cbraces);
	ft_strdel(&cbraces);
	return (expansion);
}
