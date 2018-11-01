/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:13:07 by rpinoit           #+#    #+#             */
/*   Updated: 2018/11/01 10:22:39 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	handle_quotes(t_lexer *lexer, char *cmd, int *i, int *j)
{
	char	status;

	status = STATUS_OK;
	if (!(cmd[*i] == '\"' || cmd[*i] == '\'' || cmd[*i] == '`')
	|| lexer_is_esc(cmd, *i))
		return (status);
	if (*j != *i)
	{
		lexer_token_add(lexer, cmd + *j, *i - *j, TOKEN_WORD);
		*j = *i;
	}
	if (cmd[*i] == '\"' && !lexer_is_esc(cmd, *i))
		status = lexer_token_doublequote(lexer, cmd, i, j);
	else if (cmd[*i] == '\'' && !lexer_is_esc(cmd, *i))
		status = lexer_token_singlequote(lexer, cmd, i, j);
	else if (cmd[*i] == '`' && !lexer_is_esc(cmd, *i))
		status = lexer_token_backquote(lexer, cmd, i, j);
	*j = *i;
	return (status);
}

static bool	lexer_check_n(char *cmd, char *prev)
{
	char	*number;
	bool	ret;

	ret = TRUE;
	number = ft_strndup(prev, cmd - prev);
	if (ft_strlens(number) != 1)
		ret = FALSE;
	else if (ft_isdigit((int)*number) != 1)
		ret = FALSE;
	ft_strdel(&number);
	return (ret);
}

static void	lexer_handle_match(
	t_token *match, t_lexer *lexer, char *cmd, char *prev)
{
	if (match->type == TOKEN_AGGREG)
	{
		if (cmd != prev && lexer_check_n(cmd, prev) == FALSE)
		{
			lexer_token_add(lexer, prev, cmd - prev, TOKEN_WORD);
			lexer_token_add(lexer, match->id, match->size, match->type);
		}
		else
			lexer_token_add(lexer, prev, cmd - prev + match->size, match->type);
	}
	else
	{
		if (cmd != prev)
			lexer_token_add(lexer, prev, cmd - prev, TOKEN_WORD);
		lexer_token_add(lexer, match->id, match->size, match->type);
	}
}

char		lexer_fill(t_lexer *lexer, char *cmd)
{
	int			i;
	int			j;
	t_token		*match;
	char		status;

	i = 0;
	j = 0;
	status = STATUS_OK;
	while (cmd && cmd[i])
		if ((match = lexer_token_search(cmd + i)))
		{
			lexer_handle_match(match, lexer, cmd + i, cmd + j);
			i += match->size;
			j = i;
		}
		else if ((cmd[i] == '\"' || cmd[i] == '\'' || cmd[i] == '`')
		&& !lexer_is_esc(cmd, i))
		{
			if ((status = handle_quotes(lexer, cmd, &i, &j)) != STATUS_OK)
				return (status);
		}
		else
			i++;
	(i != j) ? lexer_token_add(lexer, cmd + j, i - j, TOKEN_WORD) : 0;
	return (status);
}
