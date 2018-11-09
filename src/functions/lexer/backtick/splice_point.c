/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splice_point.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 13:44:28 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/09 14:01:30 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char		ft_is_space(char c)
{
	return (c != '\0' &&
	(
		c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r'
		|| c == ' '));
}

size_t			backtick_splice_points(char *s)
{
	int		i;
	size_t	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (ft_is_space(s[i]) && !lexer_is_esc(s, i))
			i++;
		if (s[i])
			n++;
		while (s[i] && (!ft_is_space(s[i]) || lexer_is_esc(s, i)))
			i++;
	}
	return (n);
}
