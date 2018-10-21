/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:51:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/21 19:19:37 by dlaurent         ###   ########.fr       */
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
**			[^a-d]	??????????????????????
**		{}	Curly braces
**			ok-{1..9}	   -> 1 2 3 4 5 6 7 8 9
**			ok-{a,b}	   -> a b
**			{{A,b}..2} -> \{A..2\} \{b..2\}
**			ok-{{A..b},2} -> A B C D E F G H I J K L M NO P Q R S T U V W X Y
**						  Z \[ \\ \] \^ _ \` a b 2
**			ok-{{A,b},c} -> A b c
*/

/*
** ! — history expansion.
** " — shell syntax.
** # — comment start when preceded by whitespace; zsh wildcards.
** $ — shell syntax.
** & — shell syntax.
** ' — shell syntax.
** ( — even in the middle of a word: ksh extended globs (also available in bash and zsh); zsh wildcards.
** ) (see ()
** * — sh wildcard.
** , — only inside brace expansion.
** ; — shell syntax.
** < — shell syntax.
** = — in zsh, when it's at the beginning of a file name (filename expansion with PATH lookup).
** > — shell syntax.
** ? — sh wildcard.
** [ — sh wildcard.
** \ — shell syntax.
** ] — you may get away with leaving it unquoted.
** ^ — history expansion; zsh wildcard.
** ` — shell syntax.
** { — brace expansion.
** | — shell syntax.
** } — needs to be escaped in zsh, other shells are more lenient when there's no matching opening brace.
** ~ — home directory expansion when it's at the beginning of a file name; zsh wildcard; always safe when it's the last character.
**
** |  &  ;  <  >  (  )  $  `  \  "  '  <space>  <tab>  <newline>
** *   ?   [   #   ˜   =   %
*/

#include "shell.h"

char		*sh_glob(char *str)
{
	int		i;
	char	*cbraces;
	char	*expansion;

	i = 0;
	cbraces = sh_glob_cbraces(str);
	expansion = sh_glob_pattern(str);
	return (expansion);
}
