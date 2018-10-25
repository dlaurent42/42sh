/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:12:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/25 15:29:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_command_check(t_env *env, t_env *alias, char *s)
{
	int		i;
	int		start;
	char	in_dquote;
	char	in_squote;

	i = 0;
	start = 0;
	in_dquote = 0;
	in_squote = 0;
	ft_printf(".. Enters command checks loop %s\n", s);
	while (s[i])
	{
		lexer_is_quote(s, i, &in_dquote, &in_squote);
		if (i && s[i - 1] == ' ' && !lexer_is_esc(s, i - 1) && s[i] != ' ')
			start = i;
		if ((s[i] == '*' || s[i] == '?' || s[i] == '[' || s[i] == '{')
		&& !lexer_is_esc(s, i) && !in_squote && !in_dquote)
			s = lexer_glob(s, start, i);
		if (s[i] == '$' && !lexer_is_esc(s, i) && !in_squote && !in_dquote)
			s = lexer_expand(env, s, i);
		if (s[i] != ' ' && !in_squote && !in_dquote && alias
		&& lexer_is_new_cmd(s, i))
			s = lexer_aliases(alias, s, i);
		i++;
	}
	ft_printf(".. Exits command checks loop %s\n", s);
	return (s);
}
