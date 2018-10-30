/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:52:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/30 19:39:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_lexer_glob	*add_node_lexer_glob(t_lexer_glob *current, char *s, int type)
{
	int				i;
	t_lexer_glob	*new;

	i = 0;
	if (!(new = (t_lexer_glob *)ft_memalloc(sizeof(t_lexer_glob))))
		return (NULL);
	new->head = (current) ? current->head : new;
	new->len = (current) ? current->len + 1 : 1;
	(current) ? current->next = new : 0;
	new->s = ft_strdups(lexer_backslash(s, type));
	return (new);
}

static t_lexer_glob	*add_splitted_node_lexer_glob(t_lexer_glob *current, char *s, int type)
{
	int			i;
	char		**arr;

	i = 0;
	arr = lexer_strsplit(s, ' ');
	while (arr && arr[i])
	{
		current = add_node_lexer_glob(current, arr[i], type);
		i++;
	}
	(arr) ? free (arr) : 0;
	return (current);
}

static void			lexer_glob_token_tree(t_token_tree **tree, t_lexer_glob *glob)
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

static bool			glob_conditions(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && !lexer_is_esc(str, i))
			return (FALSE);
		if ((str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == '{')
		&& !lexer_is_esc(str, i))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void				lexer_glob(t_token_tree **tree)
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
			if (glob_conditions((*tree)->tokens[i]))
				(*tree)->tokens[i] = sh_glob((*tree)->tokens[i]);
			glob = (ft_strcmps(res, (*tree)->tokens[i]) == 0)
				? add_node_lexer_glob(glob, (*tree)->tokens[i], (*tree)->t_type[i])
				: add_splitted_node_lexer_glob(glob, (*tree)->tokens[i], (*tree)->t_type[i]);
			ft_strdel(&res);
		}
		else
			glob = add_node_lexer_glob(glob, (*tree)->tokens[i], (*tree)->t_type[i]);
		i++;
	}
	return (lexer_glob_token_tree(tree, glob));
}
