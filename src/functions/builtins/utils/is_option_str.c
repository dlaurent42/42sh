/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:21:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 21:14:53 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	sh_is_option_string(char *s, char *opt)
{
	int		i;
	int		j;

	i = 1;
	if (s[0] != '-' || (s[0] == '-' && !s[1]))
		return (FALSE);
	while (s[i])
	{
		j = 0;
		while (opt[j] && opt[j] != s[i])
			j++;
		if (opt[j] == '\0')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
