/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:14:49 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/22 17:13:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*lexer_token_search(const char *cmd)
{
	const t_token	*lexic;

	lexic = lexer_lexic_singletone();
	while (lexic != NULL && lexic->id != NULL)
	{
		if (ft_strncmp(cmd, lexic->id, lexic->size) == 0)
			return ((t_token *)lexic);
		++lexic;
	}
	return (NULL);
}
