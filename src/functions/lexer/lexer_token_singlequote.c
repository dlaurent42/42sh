/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_singlequote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 12:27:00 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/19 12:56:29 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void    lexer_token_singlequote(t_lexer *lexer, const char **cmd)
{
    int i;

    i = 0;
    *cmd = *cmd + 1;
    while (cmd[0][i] != '\'')
    {
        if (cmd[0][i] == '\0')
            return ;
        ++i;
    }
    lexer_token_add(lexer, *cmd, i, TOKEN_SINGLEQUOTE);
    *cmd = *cmd + i;
}