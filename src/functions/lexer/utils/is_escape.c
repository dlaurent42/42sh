/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_escape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 16:48:28 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/25 14:36:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		lexer_is_esc(char *str, int i)
{
	int	tmp;
	int	count;

	tmp = i;
	count = 0;
	if (!str[i])
		return (FALSE);
	if (str[i] == '\\')
		while (++i && str[i] == '\\')
			count++;
	i = tmp;
	while (--i >= 0 && str[i] == '\\')
		count++;
	return (count % 2);
}
