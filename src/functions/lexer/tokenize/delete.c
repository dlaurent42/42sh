/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 14:19:56 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/24 17:36:33 by dlaurent         ###   ########.fr       */
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
