/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_new_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:56:30 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/25 14:10:11 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		lexer_is_new_cmd(char *s, int pos)
{
	int		i;

	i = pos - 1;
	while (i >= 0)
	{
		if ((s[i] == '|' || s[i] == '&' || s[i] == ';' || s[i] == '`')
		&& lexer_is_esc(s, i))
			return (TRUE);
		else if (s[i] != ' ' || lexer_is_esc(s, i))
			return (FALSE);
		i--;
	}
	if (i == 0)
		return (TRUE);
	return (FALSE);
}
