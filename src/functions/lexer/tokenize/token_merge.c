/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 14:10:48 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:49:06 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	lexer_token_merge(t_lexer *lexer, size_t i)
{
	if ((i + 1) >= lexer->size)
		return (STATUS_ERR);
	lexer->tokens[i].size += ft_strlens(lexer->tokens[i + 1].id);
	lexer->tokens[i].id = ft_strjoinf(
			lexer->tokens[i].id,
			lexer->tokens[i + 1].id,
			1);
	lexer->tokens[i].type = (lexer->tokens[i].type == TOKEN_MERGE)
		? lexer->tokens[i + 1].type
		: lexer->tokens[i].type;
	if ((i + 2) < lexer->size)
	{
		ft_strdel(&lexer->tokens[i + 1].id);
		ft_memmove(
				&lexer->tokens[i + 1],
				&lexer->tokens[i + 2],
				sizeof(t_token) * (lexer->size - (i + 2)));
	}
	else
		ft_strdel(&lexer->tokens[lexer->size - 1].id);
	lexer->size -= 1;
	return (STATUS_OK);
}
