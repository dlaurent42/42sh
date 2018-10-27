/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic_singletone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:07:24 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/27 21:28:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

const t_token	*lexer_lexic_singletone(void)
{
	static const	t_token lexic[] = {
		{"&&", 2, TOKEN_ANDIF},
		{">&", 2, TOKEN_AGGREG},
		{"<&", 2, TOKEN_AGGREG},
		{"||", 2, TOKEN_ORIF},
		{">>", 2, TOKEN_REDIR},
		{"<<", 2, TOKEN_REDIR},
		{"<", 1, TOKEN_REDIR},
		{">", 1, TOKEN_REDIR},
		{";", 1, TOKEN_SEMICOLON},
		{"|", 1, TOKEN_PIPE},
		{"\t", 1, TOKEN_BLANK},
		{"\n", 1, TOKEN_BLANK},
		{"\v", 1, TOKEN_BLANK},
		{"\f", 1, TOKEN_BLANK},
		{"\r", 1, TOKEN_BLANK},
		{" ", 1, TOKEN_BLANK},
		{NULL, 0, TOKEN_NULL}
	};

	return (lexic);
}
