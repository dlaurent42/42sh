/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_search.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:14:49 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:49:07 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_token	*lexer_token_search(char *cmd, int i)
{
	const t_token *lexic;

	lexic = lexer_lexic_singletone();
	if (cmd[i] && lexic && !lexer_is_esc(cmd, i))
		while (lexic->id)
		{
			if (ft_strncmps(cmd + i, lexic->id, lexic->size) == 0)
				return ((t_token *)lexic);
			++lexic;
		}
	return (NULL);
}
