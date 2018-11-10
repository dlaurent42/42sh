/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic_singletone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:07:24 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:49:02 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

const t_token	*lexer_lexic_singletone(void)
{
	static const	t_token lexic[] = {
		{.id = "&&", .size = 2, .type = TOKEN_ANDIF},
		{.id = ">&", .size = 2, .type = TOKEN_AGGREG},
		{.id = "<&", .size = 2, .type = TOKEN_AGGREG},
		{.id = "||", .size = 2, .type = TOKEN_ORIF},
		{.id = ">>", .size = 2, .type = TOKEN_REDIR},
		{.id = "<<", .size = 2, .type = TOKEN_HEREDOC},
		{.id = "<", .size = 1, .type = TOKEN_REDIR},
		{.id = ">", .size = 1, .type = TOKEN_REDIR},
		{.id = ";", .size = 1, .type = TOKEN_SEMICOLON},
		{.id = "&", .size = 1, .type = TOKEN_AMPERSAND},
		{.id = "|", .size = 1, .type = TOKEN_PIPE},
		{.id = "\t", .size = 1, .type = TOKEN_BLANK},
		{.id = "\n", .size = 1, .type = TOKEN_BLANK},
		{.id = "\v", .size = 1, .type = TOKEN_BLANK},
		{.id = "\f", .size = 1, .type = TOKEN_BLANK},
		{.id = "\r", .size = 1, .type = TOKEN_BLANK},
		{.id = " ", .size = 1, .type = TOKEN_BLANK},
		{.id = NULL, .size = 0, .type = TOKEN_NULL}
	};

	return (lexic);
}
