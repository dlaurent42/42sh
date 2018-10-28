/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:13:07 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/28 18:56:14 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	handle_quotes(t_lexer *lexer, const char **cmd, const char **prev)
{
	char status;

	status = STATUS_OK;
	if (**cmd == '\"')
	{
		if (*prev != *cmd)
			lexer_token_add(lexer, *prev, *cmd - *prev, TOKEN_WORD);
		status = lexer_token_doublequote(lexer, cmd);
		*prev = &(**cmd);
	}
	else if (**cmd == '\'')
	{
		if (*prev != *cmd)
			lexer_token_add(lexer, *prev, *cmd - *prev, TOKEN_WORD);
		status = lexer_token_singlequote(lexer, cmd);
		*prev = &(**cmd);
	}
	else if (**cmd == '`')
	{
		if (prev != cmd)
			lexer_token_add(lexer, *prev, *cmd - *prev, TOKEN_WORD);
		status = lexer_token_backquote(lexer, cmd);
		*prev = &(**cmd);
	}
	return (status);
}

static void	lexer_handle_match(
	t_token *match, t_lexer *lexer, const char *cmd, const char *prev)
{
	if (match->type == TOKEN_AGGREG)
		lexer_token_add(
			lexer, prev, cmd - prev + match->size, match->type);
	else
	{
		if (prev != cmd)
			lexer_token_add(lexer, prev, cmd - prev, TOKEN_WORD);
		lexer_token_add(lexer, match->id, match->size, match->type);
	}
}

char		lexer_fill(t_lexer *lexer, const char *cmd)
{
	t_token		*match;
	char		status;
	const char	*prev;

	match = NULL;
	prev = cmd;
	status = STATUS_OK;
	while (*cmd != '\0')
	{
		if ((match = lexer_token_search(cmd)))
		{
			lexer_handle_match(match, lexer, cmd, prev);
			cmd += match->size;
			prev = cmd;
		}
		else if (*cmd == '\"' || *cmd == '\'' || *cmd == '`')
		{
			if ((status = handle_quotes(lexer, &cmd, &prev)) != STATUS_OK)
				return (status);
		}
		else
			++cmd;
	}
	(prev != cmd) ? lexer_token_add(lexer, prev, cmd - prev, TOKEN_WORD) : 0;
	return (status);
}
