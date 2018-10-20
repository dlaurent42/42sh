/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 14:10:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/20 17:33:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		glob_is_esc(char *str, int i)
{
	int	tmp;
	int	count;

	tmp = i;
	count = 0;
	if (str[i] == '\\')
		while (++i && str[i] == '\\')
			count++;
	i = tmp;
	while (--i >= 0 && str[i] == '\\')
		count++;
	ft_printf("........ count esc : %d\n", count);
	return (count % 2);
}

bool		glob_need_esc(char c)
{
	if (c == '!' || c == '"' || c == '#' || c == '$' || c == '&' || c == '\''
	|| c == '(' || c == ')' || c == '*' || c == ',' || c == ';' || c == '<'
	|| c == '=' || c == '>' || c == '?' || c == '[' || c == '\\' || c == ']'
	|| c == '^' || c == '`' || c == '{' || c == '|' || c == '}' || c == '~'
	|| c == '}')
		return (TRUE);
	return (FALSE);
}

int			glob_strcountif(char *str, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && !glob_is_esc(str, i))
			count++;
		i++;
	}
	return (count);
}
