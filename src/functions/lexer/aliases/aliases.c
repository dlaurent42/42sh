/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aliases.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 13:26:30 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/25 15:19:59 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*lexer_aliases(t_env *aliases, char *s, int start)
{
	int		stop;
	char	*sub;
	char	*alias;

	stop = start + 1;
	ft_printf("... Enters lexer aliases %s\n", s);
	while ((s[stop] != '\0' && s[stop] != ' ' && s[stop] != '<'
	&& s[stop] != '>' && s[stop] != '|' && s[stop] != '&')
	|| lexer_is_esc(s, stop))
		stop++;
	sub = ft_strsub(s, start, stop - start);
	ft_printf(".... lexer aliases %s\n", sub);
	if ((alias = env_search(aliases, sub)))
	{
		lexer_repatriate(s, start, stop - start);
		s = lexer_inject_dup(s, alias, start);
	}
	ft_strdel(&sub);
	ft_printf("... Exit lexer aliases %s\n", s);
	return (s);
}
