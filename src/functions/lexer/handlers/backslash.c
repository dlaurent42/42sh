/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 20:40:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:59:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_command_replace_backslash_octal(char *s, int i)
{
	int	j;
	int	val;

	j = i + 1;
	val = 0;
	if (!ft_isdigit(s[j]))
		return ;
	while (ft_isdigit(s[j]) && j <= i + 3)
	{
		val = val * 8 + (s[j] - 48);
		j++;
	}
	if (val > 127)
		return ;
	s[i] = val;
	lexer_repatriate(s, i + 1, j - i);
}

static bool	sh_command_replace_backslah(char *s, int i)
{
	bool	is_escaped;

	is_escaped = FALSE;
	if (s[i + 1] == '\0')
		return (FALSE);
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
	(is_escaped)
		? lexer_repatriate(s, i + 1, 1)
		: sh_command_replace_backslash_octal(s, i);
	return (TRUE);
}

static void	sh_command_get_isquote(char *s, int i, char *dq, char *sq)
{
	if (s[i] == '"' && i && s[i - 1] == '=' && !(*dq || *sq))
		*dq = 2;
	else if (s[i] == '\'' && i && s[i - 1] == '=' && !(*dq || *sq))
		*sq = 2;
	if (s[i] == '"' && !(*dq || *sq))
		*dq = 1;
	else if (s[i] == '\'' && !(*dq || *sq))
		*sq = 1;
	else if (s[i] == '"' && (*dq || *sq))
		*dq = 0;
	else if (s[i] == '"' && (*dq || *sq))
		*sq = 0;
}

bool		sh_command_parse_backslash(char *s)
{
	int		i;
	char	in_dquote;
	char	in_squote;

	i = 0;
	in_dquote = 0;
	in_squote = 0;
	while (s[i])
	{
		sh_command_get_isquote(s, i, &in_dquote, &in_squote);
		if (s[i] == '\\' && (in_squote == 1 || in_dquote == 1))
		{
			if (!sh_command_replace_backslah(s, i))
				return (FALSE);
		}
		else if (s[i] == '\\' && !s[i + 1] && !in_squote && !in_dquote)
			return (FALSE);
		else if (s[i] == '\\' && !in_squote && !in_dquote && (s[i] = s[i + 1]))
			lexer_repatriate(s, i + 1, 1);
		i += (s[i]) ? 1 : 0;
	}
	return (TRUE);
}
