/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 11:17:15 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 02:26:18 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** name   A  word  consisting  only  of alphanumeric characters and under‐
**        scores, and beginning with an alphabetic character or an  under‐
**        score.  Also referred to as an identifier.
*/

bool	env_key_is_ok(char *name)
{
	int	i;

	i = 0;
	if (!name || !name[0] || (!ft_isalpha(name[0]) && name[0 != '_']))
		return (FALSE);
	while (name[++i])
	{
		if (!ft_isalnum(name[i]))
			return (FALSE);
	}
	return (TRUE);
}

bool	env_key_is_protected(char *name)
{
	int	i;

	i = 0;
	if (!name || !name[0] || name[1])
		return (FALSE);
	if (name[0] == '@' ||
		name[0] == '*' ||
		name[0] == '#' ||
		name[0] == '?' ||
		name[0] == '-' ||
		name[0] == '$' ||
		name[0] == '!' ||
		name[0] == '0')
		return (TRUE);
	return (FALSE);
}
