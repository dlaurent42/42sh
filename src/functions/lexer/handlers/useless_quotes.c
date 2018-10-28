/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:30:52 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:59:46 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_remove_useless_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '"' && str[i + 1] == '"')
		|| (str[i] == '\'' && str[i + 1] == '\''))
		{
			lexer_repatriate(str, i, 2);
			i = 0;
		}
		else
			i++;
	}
	if (str[0] == '\'' || str[0] == '"')
	{
		lexer_repatriate(str, 0, 1);
		str[ft_strlens(str) - 1] = '\0';
	}
}
