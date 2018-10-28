/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 14:10:48 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/28 18:54:46 by dlaurent         ###   ########.fr       */
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
		3);
	lexer->tokens[i].type = (lexer->tokens[i].type == TOKEN_MERGE)
	? lexer->tokens[i + 1].type
	: lexer->tokens[i].type;
	if ((i + 2) < lexer->size)
		ft_memmove(
			&lexer->tokens[i + 1],
			&lexer->tokens[i + 2],
			sizeof(t_token *) * (lexer->size - i + 2));
	lexer->size -= 1;
	return (STATUS_OK);
}
