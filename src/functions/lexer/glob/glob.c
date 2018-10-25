/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:51:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/25 15:19:48 by dlaurent         ###   ########.fr       */
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

// static char	*sh_glob_lexer_concat(char **arr)
// {
// 	int		i;
// 	char	*str;

// 	i = 0;
// 	str = NULL;
// 	while (arr && arr[i])
// 	{
// 		(str) ? str = ft_strjoinf(str, " ", 1) : 0;
// 		str = ft_strjoinf(str, arr[i], 3);
// 		i++;
// 	}
// 	(arr) ? free(arr) : 0;
// 	return (str);
// }

// static char	*sh_glob_lexer_del(char *str, char **arr)
// {
// 	int		i;

// 	i = 0;
// 	while (arr && arr[i])
// 	{
// 		ft_strdel(&arr[i]);
// 		i++;
// 	}
// 	(arr) ? free(arr) : 0;
// 	return (str);
// }

// char		*sh_glob_lexer(char *str)
// {
// 	int		i;
// 	char	**arr;
// 	char	*tmp;
// 	bool	modified;

// 	i = 0;
// 	modified = FALSE;
// 	if (!str || !(arr = lexer_strsplit(str, ' ')))
// 		return (str);
// 	while (arr && arr[i])
// 	{
// 		if (lexer_strcountif(arr[i], '[') || lexer_strcountif(arr[i], '{')
// 		|| lexer_strcountif(arr[i], '*') || lexer_strcountif(arr[i], '?'))
// 		{
// 			tmp = ft_strdups(arr[i]);
// 			arr[i] = sh_glob(arr[i]);
// 			(ft_strcmps(tmp, arr[i])) ? modified = TRUE : 0;
// 			ft_strdel(&tmp);
// 		}
// 		i++;
// 	}
// 	if (modified == FALSE)
// 		return (sh_glob_lexer_del(str, arr));
// 	ft_strdel(&str);
// 	return (sh_glob_lexer_concat(arr));
// }

// char		*lexer_glob(char *s)
// {
// 	int		i;
// 	int		start;
// 	char	in_dquote;
// 	char	in_squote;

// 	i = 0;
// 	start = 0;
// 	in_dquote = 0;
// 	in_squote = 0;
// 	while (s[i])
// 	{
// 		lexer_is_quote(s, i, &in_dquote, &in_squote);
// 		if (i && s[i - 1] == ' ' && !lexer_is_esc(s, i - 1) && s[i] != ' ')
// 			start = i;
// 		else if ((s[i] == '*' || s[i] == '?' || s[i] == '[' || s[i] == '{')
// 		&& !lexer_is_esc(s, i) && !in_squote && !in_dquote)
// 			s = lexer_glob_assess(s, start, i);
// 		i++;
// 	}
// 	return (s);
// }

char		*sh_glob(char *str)
{
	int		i;
	char	*cbraces;
	char	*expansion;
	char	**cbracessplit;

	i = 0;
	if (!str || !str[0])
		return (str);
	ft_printf(".... globbing function received %s\n", str);
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
	if (!expansion)
		return (cbraces);
	ft_strdel(&cbraces);
	return (expansion);
}

char	*lexer_glob(char *s, int start, int i)
{
	int		stop;
	char	*res;

	stop = i;
	ft_printf("... Enters lexer glob %s\n", s);
	while ((s[stop] != '\0' && s[stop] != ' ' && s[stop] != '<'
	&& s[stop] != '>' && s[stop] != '|' && s[stop] != '&')
	|| lexer_is_esc(s, stop))
		stop++;
	res = sh_glob(ft_strsub(s, start, stop - start));
	ft_printf(".... lexer glob %s\n", res);
	lexer_repatriate(s, start, stop - start);
	s = lexer_inject_dup(s, res, start);
	ft_strdel(&res);
	ft_printf("... Exit lexer glob %s\n", s);
	return (s);
}
