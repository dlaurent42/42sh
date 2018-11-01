/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:12:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/01 16:40:35 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	check_expand_conditions(char *s, int i, char in_sq)
{
	return (
	!in_sq
	&& s[i] == '$'
	&& s[i + 1] != '\0'
	&& !lexer_is_esc(s, i));
}

static bool	check_tilde_conditions(char *s, int i, char in_sq, char in_dq)
{
	return (
	!in_sq && !in_dq
	&& s[i] == '~'
	&& (s[i + 1] == '\0' || s[i + 1] == '/')
	&& (i == 0 || s[i - 1] == ' ' || s[i - 1] == '<' || s[i - 1] == '>'
		|| s[i - 1] == '|' || s[i - 1] == '&')
	&& !lexer_is_esc(s, i));
}

char		*sh_command_check(t_env *env, char *s, int type)
{
	int		i;
	int		start;
	char	in_dquote;
	char	in_squote;

	i = 0;
	start = 0;
	in_dquote = (type == TOKEN_DOUBLEQUOTE);
	in_squote = (type == TOKEN_SINGLEQUOTE);
	while (s && s[i])
	{
		if (i && s[i - 1] == ' ' && !lexer_is_esc(s, i - 1) && s[i] != ' ')
			start = i;
		if (check_tilde_conditions(s, i, in_squote, in_dquote) && env)
			s = lexer_tilde(env, s, i);
		else if (check_expand_conditions(s, i, in_squote) && env)
			s = lexer_expand(env, s, i);
		else
			i++;
	}
	return (s);
}
