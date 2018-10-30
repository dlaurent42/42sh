/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 21:08:41 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/30 21:49:35 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool			tree_splice_point(t_lexer lexer, size_t i)
{
	return (lexer.tokens[i].type == TOKEN_ANDIF
		|| lexer.tokens[i].type == TOKEN_AGGREG
		|| lexer.tokens[i].type == TOKEN_ORIF
		|| lexer.tokens[i].type == TOKEN_REDIR
		|| lexer.tokens[i].type == TOKEN_SEMICOLON
		|| lexer.tokens[i].type == TOKEN_PIPE
		|| lexer.tokens[i].type == TOKEN_REDIR
		|| lexer.tokens[i].type == TOKEN_HEREDOC);
}

static void			tree_group_token(t_lexer lexer, t_token_tree **head,
										size_t len, size_t begin)
{
	t_token_tree		*new;
	size_t				i;

	if (len == 0 || !(new = new_tree_node()))
		return ;
	new->size = len;
	new->type = (len > 1 ? 0 : get_tree_token_type(lexer.tokens[begin]));
	if (!(new->tokens = (char **)ft_memalloc(sizeof(char *) * (len + 1)))
		|| !(new->t_type = (int *)ft_memalloc(sizeof(int) * (len)))
		|| !(new->blanks = (int *)ft_memalloc(sizeof(int) * (len))))
		error_malloc_reader(g_sh, "token");
	new->tokens[len] = NULL;
	i = 0;
	while (i < len)
	{
		new->tokens[i] = ft_strdup(lexer.tokens[i + begin].id);
		new->t_type[i] = lexer.tokens[i + begin].type;
		new->blanks[i] = lexer.tokens[i + begin].blank_before;
		i++;
	}
	add_tree_to_back(head, new);
}

t_token_tree		*build_list(t_lexer lexer)
{
	size_t				i;
	size_t				len;
	t_token_tree		*head;

	i = 0;
	len = 0;
	head = NULL;
	while (i < lexer.size)
	{
		if (tree_splice_point(lexer, i))
		{
			tree_group_token(lexer, &head, len, i - len);
			tree_group_token(lexer, &head, 1, i);
			len = 0;
		}
		else
			len++;
		i++;
	}
	tree_group_token(lexer, &head, len, i - len);
	return (head);
}
