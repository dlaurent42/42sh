/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_backquote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:19:43 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/25 19:18:32 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	lexer_token_backquote(t_lexer *lexer, const char **cmd)
{
	int i;

	i = 0;
	*cmd = *cmd + 1;
	while (cmd[0][i] != '`')
	{
		if (cmd[0][i] == '\0')
			return (STATUS_BQUOTE);
		++i;
	}
	lexer_token_add(lexer, *cmd, i, TOKEN_BACKQUOTE);
	*cmd = *cmd + i + 1;
	return (STATUS_OK);
}
