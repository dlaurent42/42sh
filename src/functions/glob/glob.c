/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:51:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 23:43:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	SOURCES
** 		http://manpages.ubuntu.com/manpages/xenial/en/man7/glob.7.html
** 		http://tldp.org/LDP/abs/html/globbingref.html
**
**	PATTERNS
**
**		hidden files and folders are not considered in globing
**
**		*	Wildcard can match multiple characters
**		?	Interrogation mark can match one character
**		[]	Ranges match all patterns
**			[ab]	can match a or b
**			[a-d]	can match a, b, c or d
**			[!a-d]	cannot match a, b, c or d
**			[^a-d]	??????????????????????
**		{1..9}	Lists replace patterns
*/

#include "shell.h"
{}
char		*sh_glob(char *str)
{
	bool	res;
	t_glob	*glob;

	ft_printf("Entering glob with [%s]\n", str);
	if (!str || !(glob = (t_glob *)ft_memalloc(sizeof(t_glob))))
		return (str);
	glob->ini = str;
	glob->new = ft_strdups(str);
	res = true;
	sh_glob_brackets(glob);
	ft_printf("Exiting glob with [%s]\n", glob->new);
	return (glob->new);
}
