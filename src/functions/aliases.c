/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliases.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 15:36:20 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 16:00:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	check_alias_conditions(char *s, int i, char in_sq, char in_dq)
{
	return (
	!in_sq && !in_dq
	&& s[i] != '\0' && s[i] != ' ' && s[i] != '<' && s[i] != '>'
	&& s[i] != '|' && s[i] != '&'
	&& lexer_is_new_cmd(s, i));
}

char		*sh_replace_aliases(t_env *alias, char *s)
{
	int		i;
	int		start;
	char	in_dquote;
	char	in_squote;

	i = 0;
	start = 0;
	in_dquote = 0;
	in_squote = 0;
	while (alias && s && s[i])
	{
		lexer_is_quote(s, i, &in_dquote, &in_squote);
		if (check_alias_conditions(s, i, in_squote, in_dquote) && alias)
			s = lexer_aliases(alias, s, i);
		i++;
	}
	return (s);
}
