/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:52:35 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/06 20:40:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_lexer_glob		*add_node_lexer_glob(
	t_lexer_glob *current, char *s, int type)
{
	int				i;
	t_lexer_glob	*new;

	i = 0;
	if (!(new = (t_lexer_glob *)ft_memalloc(sizeof(t_lexer_glob))))
		return (NULL);
	new->head = (current) ? current->head : new;
	new->len = (current) ? current->len + 1 : 1;
	(current) ? current->next = new : 0;
	s = lexer_backslash(s, type);
	new->s = ft_strdupf(s);
	return (new);
}

static t_lexer_glob	*add_splitted_node_lexer_glob(
	t_lexer_glob *current, char *s, int type)
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
	ft_strdel(&s);
	(arr) ? free(arr) : 0;
	return (current);
}

static void			lexer_glob_token_tree(
	t_token_tree **tree, t_lexer_glob *glob)
{
	size_t			i;
	t_lexer_glob	*tmp;

	i = 0;
	if (!glob)
		return ;
	if (*tree && (*tree)->tokens)
		free((*tree)->tokens);
	if (!((*tree)->tokens = (char **)ft_memalloc(
		sizeof(char *) * (glob->len + 1))))
		return ;
	glob = glob->head;
	while (glob)
	{
		tmp = glob->next;
		(*tree)->tokens[i] = ft_strdupf(glob->s);
		free(glob);
		glob = tmp;
		i++;
	}
}

static void			do_glob(t_token_tree **t, int i, t_lexer_glob **glob)
{
	char	*res;

	res = ft_strdups((*t)->tokens[i]);
	if (glob_conditions((*t)->tokens[i]))
		(*t)->tokens[i] = sh_glob((*t)->tokens[i]);
	*glob = (ft_strcmps(res, (*t)->tokens[i]) == 0)
		? add_node_lexer_glob(*glob, (*t)->tokens[i], (*t)->t_type[i])
		: add_splitted_node_lexer_glob(
			*glob, (*t)->tokens[i], (*t)->t_type[i]);
	ft_strdel(&res);
}

void				lexer_glob(t_shell *sh, t_env *env, t_token_tree **t)
{
	int				i;
	t_lexer_glob	*glob;

	i = 0;
	glob = NULL;
	while ((*t)->tokens[i])
	{
		if ((*t)->t_type[i] == TOKEN_WORD)
			do_glob(t, i, &glob);
		else if ((*t)->t_type[i] == TOKEN_BACKQUOTE)
		{
			(*t)->tokens[i] = backtick_prep(sh, env, (*t)->tokens[i]);
			glob = (backtick_splice_points((*t)->tokens[i]) > 0) ?
			add_node_lexer_backtick(glob, (*t)->tokens[i], (*t)->t_type[i]) :
			add_node_lexer_glob(glob, (*t)->tokens[i], (*t)->t_type[i]);
		}
		else
			glob = add_node_lexer_glob(glob, (*t)->tokens[i], (*t)->t_type[i]);
		i++;
	}
	return (lexer_glob_token_tree(t, glob));
}
