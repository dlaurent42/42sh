/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_doublequote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:12:58 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/22 16:07:22 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lexer_token_doublequote(t_lexer *lexer, const char **cmd)
{
	int	i;

	i = 0;
	*cmd = *cmd + 1;
	while (cmd[0][i] != '\"')
	{
		if (cmd[0][i] == '\0')
			break ;
		++i;
	}
	lexer_token_add(lexer, *cmd, i, TOKEN_DOUBLEQUOTE);
	*cmd = *cmd + i;
}
