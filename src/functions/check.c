/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:12:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 17:35:20 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	check_glob_conditions(char *s, int i, char in_sq, char in_dq)
{
	return (
	!in_sq && !in_dq
	&& (s[i] == '*' || s[i] == '?' || s[i] == '[' || s[i] == '{')
	&& !lexer_is_esc(s, i));
}

static bool	check_expand_conditions(char *s, int i, char in_sq, char in_dq)
{
	return (
	!in_sq && !in_dq
	&& s[i] == '$'
	&& !lexer_is_esc(s, i));
}

static bool	check_tilde_conditions(char *s, int i, char in_sq, char in_dq)
{
	return (
	!in_sq && !in_dq
	&& s[i] == '~'
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
	in_dquote = (type == TOKEN_SINGLEQUOTE);
	in_squote = (type == TOKEN_DOUBLEQUOTE);
	while (s[i])
	{
		// lexer_is_quote(s, i, &in_dquote, &in_squote);
		if (i && s[i - 1] == ' ' && !lexer_is_esc(s, i - 1) && s[i] != ' ')
			start = i;
		if (check_tilde_conditions(s, i, in_squote, in_squote) && env)
			s = lexer_tilde(env, s, i);
		if (check_glob_conditions(s, i, in_squote, in_dquote))
			s = lexer_glob(s, start, i);
		if (check_expand_conditions(s, i, in_squote, in_dquote) && env)
			s = lexer_expand(env, s, i);
		i++;
	}
	return (s);
}
