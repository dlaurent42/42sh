/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 19:39:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/30 19:49:54 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*lexer_replace_backslash_octal(char *s, int i)
{
	int	j;
	int	val;

	j = i + 1;
	val = 0;
	if (!ft_isdigit(s[j]))
		return (s);
	while (ft_isdigit(s[j]) && j <= i + 3)
	{
		val = val * 8 + (s[j] - 48);
		j++;
	}
	if (val > 127)
		return (s);
	s[i] = val;
	lexer_repatriate(&(*s), i + 1, j - i);
	return (s);
}

static char	*lexer_replace_backslash(char *s, int i)
{
	bool	is_escaped;

	is_escaped = FALSE;
	if (s[i + 1] == '\\' && (is_escaped = TRUE))
		s[i] = '\\';
	else if (s[i + 1] == 'a' && (is_escaped = TRUE))
		s[i] = '\a';
	else if (s[i + 1] == 'b' && (is_escaped = TRUE))
		s[i] = '\b';
	else if (s[i + 1] == 'f' && (is_escaped = TRUE))
		s[i] = '\f';
	else if (s[i + 1] == 'n' && (is_escaped = TRUE))
		s[i] = '\n';
	else if (s[i + 1] == 'r' && (is_escaped = TRUE))
		s[i] = '\r';
	else if (s[i + 1] == 't' && (is_escaped = TRUE))
		s[i] = '\t';
	else if (s[i + 1] == 'v' && (is_escaped = TRUE))
		s[i] = '\v';
	else if (ft_isdigit(s[i + 1]))
		s = lexer_replace_backslash_octal(s, i);
	(is_escaped) ? lexer_repatriate(&(*s), i + 1, 1) : 0;
	return (s);
}

char		*lexer_backslash(char *s, int type)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\\' && s[i + 1] && type == TOKEN_WORD)
			lexer_repatriate(&(*s), i, 1);
		if (s[i] == '\\' && s[i + 1]
		&& (type == TOKEN_SINGLEQUOTE || type == TOKEN_DOUBLEQUOTE))
			s = lexer_replace_backslash(s, i);
		i++;
	}
	return (s);
}
