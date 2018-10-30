/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 19:51:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/30 16:18:01 by dlaurent         ###   ########.fr       */
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

t_lexer_glob	*add_node_lexer_glob(t_lexer_glob *current, char *s)
{
	t_lexer_glob	*new;

	if (!(new = (t_lexer_glob *)ft_memalloc(sizeof(t_lexer_glob))))
		return (NULL);
	new->head = (current) ? current->head : new;
	new->len = (current) ? current->len + 1 : 1;
	(current) ? current->next = new : 0;
	new->s = ft_strdups(s);
	return (new);
}

t_lexer_glob	*add_splitted_node_lexer_glob(t_lexer_glob *current, char *s)
{
	int			i;
	char		**arr;

	i = 0;
	arr = lexer_strsplit(s, ' ');
	while (arr && arr[i])
	{
		current = add_node_lexer_glob(current, arr[i]);
		i++;
	}
	(arr) ? free (arr) : 0;
	return (current);
}

void	lexer_glob_token_tree(t_token_tree **tree, t_lexer_glob *glob)
{
	size_t			i;
	t_lexer_glob	*tmp;

	i = 0;
	if (!glob)
		return ;
	if (!((*tree)->tokens = (char **)ft_memalloc(sizeof(char *) * (glob->len + 1))))
		return ;
	glob = glob->head;
	while (glob)
	{
		tmp = glob->next;
		(*tree)->tokens[i] = ft_strdups(glob->s);
		free(glob);
		glob = tmp;
		i++;
	}
}

void	lexer_glob(t_token_tree **tree)
{
	int				i;
	char			*res;
	t_lexer_glob	*glob;

	i = 0;
	glob = NULL;
	while ((*tree)->tokens[i])
	{
		if ((*tree)->t_type[i] == TOKEN_WORD)
		{
			res = ft_strdups((*tree)->tokens[i]);
			(*tree)->tokens[i] = sh_glob((*tree)->tokens[i]);
			glob = (ft_strcmps(res, (*tree)->tokens[i]) == 0)
				? add_node_lexer_glob(glob, (*tree)->tokens[i])
				: add_splitted_node_lexer_glob(glob, (*tree)->tokens[i]);
			ft_strdel(&res);
		}
		else
			glob = add_node_lexer_glob(glob, (*tree)->tokens[i]);
		i++;
	}
	return (lexer_glob_token_tree(tree, glob));
}