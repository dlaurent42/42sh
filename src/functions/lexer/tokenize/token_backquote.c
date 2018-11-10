/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_backquote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:19:43 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:49:04 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	lexer_token_backquote(t_lexer *lexer, char *cmd, int *i, int *j)
{
	*i = *i + 1;
	while (cmd[*i] != '`' || (cmd[*i] == '`' && lexer_is_esc(cmd, *i)))
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
