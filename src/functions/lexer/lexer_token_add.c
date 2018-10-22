/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_add.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 12:13:53 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/22 13:11:01 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void        lexer_token_add(t_lexer *lexer, const char *src, size_t size, t_token_type type)
{
    t_token new;

    new.id = ft_strndup(src, size);
    new.size = size;
    new.type = type;
    dyn_arr_add((t_array *)lexer, (void *)&new, 1, sizeof(t_token));
}