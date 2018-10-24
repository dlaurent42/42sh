/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_stop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:12:40 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 17:10:57 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	sh_glob_cbraces_start_stop(t_cbraces *cb)
{
	int		i;
	int		more;

	i = -1;
	more = 0;
	while (cb->str[++i] && !(cb->start > -1 && cb->stop > -1 && more == 0))
		if (cb->start > -1 && cb->str[i] == '{' && !lexer_is_esc(cb->str, i))
			more++;
		else if (cb->stop > -1 && cb->str[i] == '{'
		&& !lexer_is_esc(cb->str, i))
			return (FALSE);
		else if (cb->start == -1 && cb->str[i] == '}'
		&& !lexer_is_esc(cb->str, i))
			return (FALSE);
		else if (cb->str[i] == '{' && !lexer_is_esc(cb->str, i))
			cb->start = i;
		else if (cb->str[i] == '}' && more && !lexer_is_esc(cb->str, i))
			more--;
		else if (cb->str[i] == '}' && !lexer_is_esc(cb->str, i))
			cb->stop = i;
	if (cb->start > -1 && cb->stop > -1 && more == 0)
		return (TRUE);
	return (FALSE);
}
