/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_empty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 14:53:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 14:55:44 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		lexer_is_empty(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
