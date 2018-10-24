/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 10:16:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 17:00:31 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_command_expansion_criteria(char c)
{
	return (ft_isalnum(c) || c == '{' || c == '?');
}

static int	sh_command_expansion_len(t_shell *sh, char *str, int i)
{
	int		len;
	char	delim;

	if (str[i] == '?')
		return (str_size_base(10, ft_atoi(env_search(sh->env, "0"))) + 1);
	else if (str[i] == '{' && str[i + 1] == '?' && str[i + 2] == '}')
		return (str_size_base(10, ft_atoi(env_search(sh->env, "0"))) + 2);
	delim = (str[i] == '{') ? '}' : 0;
	len = (delim) ? 2 : 1;
	i += (delim) ? 1 : 0;
	while (str[i]
	&& ((delim && str[i] != delim) || (!delim && ft_isalnum(str[i]))))
	{
		len++;
		i++;
	}
	return (len);
}

static char	*sh_command_expansion_val(t_shell *sh, t_env *env, char *str)
{
	char *tmp;

	tmp = NULL;
	(void)sh;
	tmp = (env_search(env, str))
		? ft_strdups(env_search(env, str))
		: ft_strdup("");
	ft_strdel(&str);
	return (tmp);
}

void		sh_command_expand_dollars(t_shell *sh, t_env *env, char *str)
{
	int		i;
	int		len;
	bool	in_dquote;
	bool	in_squote;
	char	*expansion;

	i = -1;
	in_dquote = FALSE;
	in_squote = FALSE;
	while (str[++i])
		if (str[i] == '"')
			in_dquote = (in_dquote || in_squote) ? FALSE : TRUE;
		else if (str[i] == '\'')
			in_squote = (in_dquote || in_squote) ? FALSE : TRUE;
		else if (str[i] == '$' && !in_squote
		&& sh_command_expansion_criteria(str[i + 1]))
		{
			len = sh_command_expansion_len(sh, str, i + 1);
			expansion = (str[i + 1] == '{')
			? sh_command_expansion_val(sh, env, ft_strsub(str, i + 2, len - 2))
			: sh_command_expansion_val(sh, env, ft_strsub(str, i + 1, len - 1));
			lexer_repatriate(str, i, len + 1);
			lexer_inject_dup(str, expansion, i);
			ft_strdel(&expansion);
		}
}
