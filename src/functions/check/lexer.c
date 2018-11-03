/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:29:40 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/03 18:27:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	is_operator(t_token_type type)
{
	return (type >= TOKEN_ANDIF && type <= TOKEN_HEREDOC);
}

static bool	is_error_token_plus_one(t_lexer *l, t_token t, int i)
{
	return (is_operator(t.type) && (i == 0
	|| l->tokens[i + 1].type == TOKEN_SEMICOLON
	|| is_operator(l->tokens[i + 1].type)
	|| (i - 1 >= 0 && l->tokens[i - 1].type == TOKEN_SEMICOLON)));
}

static bool	is_error_subshell(t_lexer *l, t_token t, int i)
{
	return (t.type == TOKEN_SUBSHELL
	&& ((l->tokens[i + 1].type >= TOKEN_SINGLEQUOTE)
	|| (i && l->tokens[i - 1].type >= TOKEN_SINGLEQUOTE)));
}

char		sh_command_check_lexer(t_shell *sh, t_lexer *l)
{
	int		i;
	char	status;
	t_token	t;

	i = -1;
	status = STATUS_OK;
	while (++i < (int)l->size)
	{
		t = l->tokens[i];
		if ((i + 1) >= (int)l->size && t.type == TOKEN_PIPE)
			return (STATUS_PIPE);
		else if ((i + 1) >= (int)l->size && is_operator(t.type))
			return (parse_error("\\n"));
		else if (is_error_token_plus_one(l, t, i) || is_error_subshell(l, t, i))
			return (parse_error(l->tokens[i].id));
		else if (t.type == TOKEN_AGGREG && lexer_token_merge(l, i) != STATUS_OK)
			return (parse_error("\\n"));
		else if (l->tokens[i].type == TOKEN_HEREDOC)
			if ((status = sh_heredoc(sh, l->tokens[i + 1].id)) == -1)
				return (status);
	}
	return (status);
}
