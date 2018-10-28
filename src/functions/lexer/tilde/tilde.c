/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:53:30 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 18:41:19 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*lexer_tilde(t_env *env, char *s, int i)
{
	char		*pwd;
	t_passwd	*pw;

	pw = getpwuid(getuid());
	if (!(pwd = env_search(env, "HOME")))
		pwd = pw->pw_dir;
	lexer_repatriate(s, i, 1);
	lexer_inject_dup(s, pwd, i);
	return (s);
}
