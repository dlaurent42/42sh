/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_backquote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:19:43 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/31 15:05:59 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	lexer_token_backquote(t_lexer *lexer, char *cmd, int *i, int *j)
{
	*i = *i + 1;
	while (cmd[*i] != '`' && !lexer_is_esc(cmd, *i))
	{
		if (cmd[*i] == '\0')
			return (STATUS_BQUOTE);
		*i = *i + 1;
	}
	*j = *j + 1;
	lexer_token_add(lexer, cmd + *j, *i - *j, TOKEN_BACKQUOTE);
	*i = *i + 1;
	return (STATUS_OK);
}
