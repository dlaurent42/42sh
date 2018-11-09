/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 19:09:51 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 18:37:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	manage_quotes(char *cmd, int i)
{
	bool	found;

	found = FALSE;
	if (cmd[i] == '\'' && !lexer_is_esc(cmd, i) && (found = TRUE))
		while (cmd[++i] && cmd[i] != '\'')
			;
	else if (cmd[i] == '\"' && !lexer_is_esc(cmd, i) && (found = TRUE))
		while (cmd[++i] &&
		(cmd[i] != '\"' || (cmd[i] == '\"' && lexer_is_esc(cmd, i))))
			;
	if (!cmd[i])
		return (-1);
	return (i);
}

static bool	lexer_handle_subshell_condition(char *cmd, size_t count, int i)
{
	return ((cmd[i] == ')' && (count || lexer_is_esc(cmd, i)))
	|| cmd[i] != ')');
}

char		lexer_handle_subshell(t_lexer *lexer, char *cmd, int *i, int *j)
{
	int		move;
	size_t	count;

	count = 0;
	*i = *i + 1;
	while (lexer_handle_subshell_condition(cmd, count, *i))
	{
		if (cmd[*i] == '\0')
			return (STATUS_SUBSHELL);
		if ((move = manage_quotes(cmd, *i)) == -1)
			return (STATUS_OK);
		*i = move;
		if (cmd[*i] == '(' && !lexer_is_esc(cmd, *i))
			count++;
		else if (cmd[*i] == ')' && count == 0 && !lexer_is_esc(cmd, *i))
			break ;
		else if (cmd[*i] == ')' && count && !lexer_is_esc(cmd, *i))
			count--;
		*i = *i + 1;
	}
	*j = *j + 1;
	lexer_token_add(lexer, cmd + *j, *i - *j, TOKEN_SUBSHELL);
	*i = *i + 1;
	*j = *i;
	return (STATUS_OK);
}
