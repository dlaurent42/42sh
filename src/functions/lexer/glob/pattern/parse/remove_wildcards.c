/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:31:55 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 10:57:06 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*glob_remove_wildcars(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '*' && str[i + 1] == '*'
		&& !glob_in_range(str, i) && i && str[i - 1] != '/')
			lexer_repatriate(str, i, 1);
		else if (str[i] == '*' && str[i + 1] == '*'
		&& !glob_in_range(str, i) && ((str[i + 2] && str[i + 2] != '/')
		|| !str[i + 2]))
			lexer_repatriate(&(*str), i, 1);
		else
			i++;
	}
	return (str);
}
