/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:14:49 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/31 11:43:55 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*lexer_token_search(char *cmd)
{
	const t_token *lexic;

	lexic = lexer_lexic_singletone();
	if (cmd && lexic)
		while (lexic->id)
		{
			if (ft_strncmps(cmd, lexic->id, lexic->size) == 0)
				return ((t_token *)lexic);
			++lexic;
		}
	return (NULL);
}
