/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_singlequote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 12:27:00 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:49:08 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	lexer_token_singlequote(t_lexer *lexer, char *cmd, int *i, int *j)
{
	*i = *i + 1;
	while (cmd[*i] != '\'')
	{
		if (cmd[*i] == '\0')
			return (STATUS_SQUOTE);
		*i = *i + 1;
	}
	*j = *j + 1;
	lexer_token_add(lexer, cmd + *j, *i - *j, TOKEN_SINGLEQUOTE);
	*i = *i + 1;
	return (STATUS_OK);
}
