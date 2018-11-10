/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_doublequote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:12:58 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:49:05 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	lexer_token_doublequote(t_lexer *lexer, char *cmd, int *i, int *j)
{
	*i = *i + 1;
	while (cmd[*i] != '\"' || (cmd[*i] == '\"' && lexer_is_esc(cmd, *i)))
	{
		if (cmd[*i] == '\0')
			return (STATUS_DQUOTE);
		*i = *i + 1;
	}
	*j = *j + 1;
	lexer_token_add(lexer, cmd + *j, *i - *j, TOKEN_DOUBLEQUOTE);
	*i = *i + 1;
	return (STATUS_OK);
}
