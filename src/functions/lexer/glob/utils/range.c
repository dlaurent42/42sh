/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:33:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:58:20 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	glob_in_range(char *str, int pos)
{
	int		i;
	bool	in_range;

	i = 0;
	in_range = FALSE;
	if (pos == 0)
		return (FALSE);
	while (str[i] && i < pos)
	{
		if (str[i] == '[' && !lexer_is_esc(str, i))
			in_range = TRUE;
		else if (str[i] == ']' && !lexer_is_esc(str, i)
		&& in_range && i && str[i - 1] != '[')
			in_range = FALSE;
		i++;
	}
	if (!str[i] && in_range)
		return (FALSE);
	return (in_range);
}
