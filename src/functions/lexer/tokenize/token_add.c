/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:13:53 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/31 15:03:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lexer_token_add(t_lexer *lexer, char *src, size_t size,
	t_token_type type)
{
	t_token new;

	if (size == 0)
		return ;
	if (type != TOKEN_BLANK)
	{
		new.id = ft_strndup(src, size);
		new.size = size;
		new.type = type;
		new.blank_before = lexer->word;
		dyn_arr_add((t_array *)lexer, (void *)&new, 1, sizeof(t_token));
		lexer->word = 0;
	}
	else
		lexer->word = 1;
}
