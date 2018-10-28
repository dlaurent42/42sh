/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_singlequote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 12:27:00 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 19:16:52 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	lexer_token_singlequote(t_lexer *lexer, const char **cmd)
{
	int i;

	i = 0;
	*cmd = *cmd + 1;
	while (cmd[0][i] != '\'')
	{
		if (cmd[0][i] == '\0')
			return (STATUS_SQUOTE);
		++i;
	}
	lexer_token_add(lexer, *cmd, i, TOKEN_SINGLEQUOTE);
	*cmd = *cmd + i + 1;
	return (STATUS_OK);
}
