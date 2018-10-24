/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 14:19:56 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/22 16:05:07 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lexer_delete(t_lexer *lexer)
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
}
