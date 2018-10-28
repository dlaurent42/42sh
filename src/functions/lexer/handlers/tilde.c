/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 19:58:11 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 17:00:31 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_command_get_isquote(char *s, int i, char *dq, char *sq)
{
	if (!s)
		return ;
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

static void	sh_command_tilde_replace(t_shell *sh, t_env *env, char *str, int i)
{
	char		*s;
	t_passwd	*pw;

	(void)sh;
	pw = getpwuid(getuid());
	s = (env_search(env, "HOME")) ? env_search(env, "HOME") : pw->pw_dir;
	lexer_repatriate(str, i, 1);
	lexer_inject_dup(str, s, i);
}

void		sh_command_expand_tile(t_shell *sh, t_env *env, char *str)
{
	int		i;
	char	in_dquote;
	char	in_squote;

	i = 0;
	in_dquote = FALSE;
	in_squote = FALSE;
	while (str[i])
	{
		sh_command_get_isquote(str, i, &in_dquote, &in_squote);
		if (!in_dquote && !in_squote && str[i] == '~'
		&& (i == 0 || (i && (str[i - 1] == ' ' || str[i - 1] == '\t'))))
			sh_command_tilde_replace(sh, env, str, i);
		i++;
	}
}
