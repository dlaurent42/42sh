/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:14:49 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/27 21:06:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token *lexer_token_search(const char *cmd)
{
	const t_token *lexic;

	lexic = lexer_lexic_singletone();
	if (!cmd)
		return (NULL);
	if (lexic != NULL)
	{
		while (lexic->id != NULL)
		{
			if (ft_strncmp(cmd, lexic->id, lexic->size) == 0)
				return ((t_token *)lexic);
			++lexic;
		}
	}
	return (NULL);
}
