/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strcountif_esc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:49:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:58:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			lexer_strcountif(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && !lexer_is_esc(str, i))
			count++;
		i++;
	}
	return (count);
}
