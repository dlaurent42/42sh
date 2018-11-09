/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 13:29:40 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 17:30:23 by azaliaus         ###   ########.fr       */
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
	return ((i == 0 && t.type == TOKEN_AMPERSAND && t.id[0] == '&')
	|| (i && t.blank_before == 0 && t.id
	&& (t.id[0] == '(' || t.id[0] == ')')
	&& l->tokens[i - 1].type >= TOKEN_SINGLEQUOTE));
}

char		sh_command_check_lexer(t_shell *sh, t_lexer *l)
{
	int		i;
	char	status;

	i = -1;
	status = STATUS_OK;
	while (++i < (int)l->size)
		if ((i + 1) >= (int)l->size && l->tokens[i].type == TOKEN_PIPE)
			return (STATUS_PIPE);
		else if ((i + 1) >= (int)l->size && l->tokens[i].type >= TOKEN_ANDIF
		&& l->tokens[i].type <= TOKEN_HEREDOC)
			return (parse_error("\\n"));
		else if (is_error_token_minus_one(l, l->tokens[i], i))
			return (parse_error(l->tokens[i - 1].id));
		else if (is_error_token_plus_one(l, l->tokens[i], i))
			return (parse_error(l->tokens[i + 1].id));
		else if (is_error_token_current(l, l->tokens[i], i))
			return (parse_error(l->tokens[i].id));
		else if (l->tokens[i].type == TOKEN_AGGREG
		&& lexer_token_merge(l, i) != STATUS_OK)
			return (parse_error("\\n"));
		else if (l->tokens[i].type == TOKEN_HEREDOC && (i + 1) <= (int)l->size)
			if ((status = sh_heredoc(sh, l->tokens[i + 1].id)) == -1)
				return (status);
	return (sh_heredoc_orga(l, status));
}
