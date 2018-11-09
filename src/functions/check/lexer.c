/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:29:40 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 10:25:02 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	is_error_subshell(t_lexer *l, t_token t, int i, char direction)
{
	if (direction == 1 && t.type == TOKEN_SUBSHELL && (((i + 1) < (int)l->size
	&& l->tokens[i + 1].type >= TOKEN_SINGLEQUOTE)))
		return (TRUE);
	return (direction == -1 && t.type == TOKEN_SUBSHELL &&
	(i && l->tokens[i - 1].type >= TOKEN_SINGLEQUOTE));
}

static bool	is_error_token_plus_one(t_lexer *l, t_token t, int i)
{
	return (is_error_subshell(l, t, i, 1)
	|| (t.type >= TOKEN_ANDIF && t.type <= TOKEN_HEREDOC && (i == 0
	|| ((i + 1) <= (int)l->size && l->tokens[i + 1].type == TOKEN_SEMICOLON)
	|| ((i + 1) <= (int)l->size && l->tokens[i + 1].type >= TOKEN_ANDIF
	&& l->tokens[i + 1].type <= TOKEN_HEREDOC))));
}

static bool	is_error_token_minus_one(t_lexer *l, t_token t, int i)
{
	return (is_error_subshell(l, t, i, -1)
	|| (t.type >= TOKEN_ANDIF && t.type <= TOKEN_HEREDOC
	&& i && l->tokens[i - 1].type == TOKEN_SEMICOLON));
}

static bool	is_error_token_current(t_lexer *l, t_token t, int i)
{
	return (i && t.blank_before == 0 && t.id
	&& (t.id[0] == '(' || t.id[0] == ')')
	&& l->tokens[i - 1].type >= TOKEN_SINGLEQUOTE);
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
		else if ((i + 1) >= (int)l->size
		&& t.type >= TOKEN_ANDIF && t.type <= TOKEN_HEREDOC)
			return (parse_error("\\n"));
		else if (is_error_token_minus_one(l, t, i))
			return (parse_error(l->tokens[i - 1].id));
		else if (is_error_token_plus_one(l, t, i))
			return (parse_error(l->tokens[i + 1].id));
		else if (is_error_token_current(l, t, i))
			return (parse_error(l->tokens[i].id));
		else if (t.type == TOKEN_AGGREG && lexer_token_merge(l, i) != STATUS_OK)
			return (parse_error("\\n"));
		else if (t.type == TOKEN_HEREDOC && (i + 1) <= (int)l->size)
			if ((status = sh_heredoc(sh, l->tokens[i + 1].id)) == -1)
				return (status);
	}
	return (status);
}
