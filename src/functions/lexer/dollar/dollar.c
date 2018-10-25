/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 19:59:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/25 14:39:59 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*sh_dollar_expansion(char *str, t_env *env)
{
	char	*expanded;
	char	*result;

	expanded = NULL;
	if (!str || str[0] != '$' || !str[1] || !env)
		return (str);
	expanded = (str[1] == '{')
		? ft_strsub(str, 2, ft_strlens(str) - 3)
		: ft_strdups(str + 1);
	result = ft_strdups(env_search(env, expanded));
	ft_strdel(&expanded);
	if (!result)
		return (str);
	ft_strdel(&str);
	return (result);
}

char		*lexer_expand(t_env *env, char *s, int start)
{
	int		stop;
	char	*expanded;

	stop = start + 1;
	if (s[stop])
		return (s);
	if (s[stop] == '{')
		while ((s[stop] != '\0' && s[stop] != '}') || lexer_is_esc(s, stop))
			stop++;
	else
		while ((s[stop] != '\0' && s[stop] != ' ' && s[stop] != '<'
		&& s[stop] != '>' && s[stop] != '|' && s[stop] != '&')
		|| lexer_is_esc(s, stop))
			stop++;
	expanded = sh_dollar_expansion(ft_strsub(s, start, stop - start), env);
	lexer_repatriate(s, start, stop - start);
	s = lexer_inject_dup(s, expanded, start);
	ft_strdel(&expanded);
	return (s);
}
