/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   espace.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 14:10:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/19 14:46:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		glob_is_esc(char *str, int i)
{
	int	tmp;
	int	count;

	tmp = i;
	count = (str[i] == '\\') ? 1 : 0;
	while (++i && str[i] == '\\')
		count++;
	i = tmp;
	while (--i >= 0 && str[i] == '\\')
		count++;
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
	bool	is_esc;

	i = 0;
	while (str[i])
	{
		if (str[i] == c && !glob_is_esc(str, i))
			count++;
		i++;
	}
	return (count);
}
