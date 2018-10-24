/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:13:07 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/24 18:22:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	handle_quotes(t_lexer *lexer, const char **cmd, const char **prev)
{
	if (**cmd == '\"')
	{
		if (*prev != *cmd)
			lexer_token_add(lexer, *prev, *cmd - *prev, TOKEN_MERGE);
		lexer_token_doublequote(lexer, cmd);
		return (1);
	}
	else if (**cmd == '\'')
	{
		if (*prev != *cmd)
			lexer_token_add(lexer, *prev, *cmd - *prev, TOKEN_MERGE);
		lexer_token_singlequote(lexer, cmd);
		return (1);
	}
	else if (**cmd == '`')
	{
		if (*prev != *cmd)
			lexer_token_add(lexer, *prev, *cmd - *prev, TOKEN_MERGE);
		lexer_token_backquote(lexer, cmd);
		return (1);
	}
	return (0);
}

char		lexer_fill(t_lexer *lexer, const char *cmd)
{
	t_token		*match;
	const char	*prev;

	prev = cmd;
	if (lexer_is_empty((char *)cmd))
		return (-1);
	while (*cmd != '\0')
	{
		match = lexer_token_search(cmd);
		if (match != NULL)
		{
			if (prev != cmd)
				lexer_token_add(lexer, prev, cmd - prev, TOKEN_WORD);
			if (match->type != TOKEN_BLANK)
				lexer_token_add(lexer, match->id, match->size, match->type);
			cmd += match->size;
			prev = cmd;
		}
		else if (handle_quotes(lexer, &cmd, &prev))
			prev = cmd;
		else
			++cmd;
	}
	(prev != cmd) ? lexer_token_add(lexer, prev, cmd - prev, TOKEN_WORD) : 0;
	return (0);
}
