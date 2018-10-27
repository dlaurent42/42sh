/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:13:07 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/27 17:21:23 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char handle_quotes(t_lexer *lexer, const char **cmd, const char **prev)
{
	char status;

	status = STATUS_OK;
	if (**cmd == '\"')
	{
		if (*prev != *cmd)
			lexer_token_add(lexer, *prev, *cmd - *prev, TOKEN_MERGE);
		status = lexer_token_doublequote(lexer, cmd);
		*prev = &(**cmd);
	}
	else if (**cmd == '\'')
	{
		if (*prev != *cmd)
			lexer_token_add(lexer, *prev, *cmd - *prev, TOKEN_MERGE);
		status = lexer_token_singlequote(lexer, cmd);
		*prev = &(**cmd);
	}
	else if (**cmd == '`')
	{
		if (*prev != *cmd)
			lexer_token_add(lexer, *prev, *cmd - *prev, TOKEN_MERGE);
		status = lexer_token_backquote(lexer, cmd);
		*prev = &(**cmd);
	}
	return (status);
}

char lexer_fill(t_lexer *lexer, const char *cmd)
{
	t_token *match;
	const char *prev;
	char status;

	prev = cmd;
	status = STATUS_OK;
	if (lexer_is_empty((char *)cmd))
		return (-1);
	while (*cmd != '\0')
	{
		match = lexer_token_search(cmd);
		if (match != NULL)
		{
			if (match->type == TOKEN_AGGREG)
				lexer_token_add(lexer, prev, cmd - prev + match->size, match->type);
			else
			{
				if (prev != cmd)
					lexer_token_add(lexer, prev, cmd - prev, TOKEN_WORD);
				if (match->type != TOKEN_BLANK)
					lexer_token_add(lexer, match->id, match->size, match->type);
			}
			cmd += match->size;
			prev = cmd;
		}
		else if ((*cmd == '\"' || *cmd == '\'' || *cmd == '`') && ((status = handle_quotes(lexer, &cmd, &prev)) != STATUS_OK))
			return (status);
		else
			++cmd;
	}
	(prev != cmd) ? lexer_token_add(lexer, prev, cmd - prev, TOKEN_WORD) : 0;
	return (status);
}