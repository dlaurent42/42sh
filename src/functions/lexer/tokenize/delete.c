/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 14:19:56 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:49:01 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	lexer_delete(t_lexer *lexer, char status)
{
	t_token	*token_tmp;
	size_t	index;

	index = 0;
	while (index < lexer->size)
	{
		token_tmp = &lexer->tokens[index];
		ft_memdel((void **)&token_tmp->id);
		++index;
	}
	ft_memdel((void **)&lexer->tokens);
	return (status);
}
