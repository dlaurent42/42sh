/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:53:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/08 14:03:25 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		lexer_is_empty(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if ((str[i] < '\a' || str[i] > '\r') && str[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
