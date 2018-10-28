/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_escaped_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 01:46:51 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/28 20:33:48 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char				*auto_get_escaped_str(char *str)
{
	char			*new_str;
	char			*ptr;
	char			len;

	ptr = str;
	len = 0;
	while (*ptr && ++len)
	{
		if (lexer_need_esc(*(ptr++)))
			len++;
	}
	if (!(new_str = ft_strnew(len)))
		return (NULL);
	ptr = new_str;
	while (*str)
	{
		if (lexer_need_esc(*str))
			*(ptr++) = '\\';
		*(ptr++) = *(str++);
	}
	return (new_str);
}
