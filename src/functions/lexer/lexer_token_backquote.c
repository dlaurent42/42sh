/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_backquote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:19:43 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/22 16:06:27 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lexer_token_backquote(t_lexer *lexer, const char **cmd)
{
	int i;

	i = 0;
	*cmd = *cmd + 1;
	while (cmd[0][i] != '`')
	{
		if (cmd[0][i] == '\0')
			break ;
		++i;
	}
	lexer_token_add(lexer, *cmd, i, TOKEN_BACKQUOTE);
	*cmd = *cmd + i;
}
