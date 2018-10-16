/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:20:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/15 19:40:44 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		env_initialize_local(t_shell *sh)
{
	char		*f;
	char		*path;
	char		*shlvl;
	t_passwd	*pw;

	path = NULL;
	if (!(env_search(sh->env, "TERM")))
		env_insert(sh, sh->env, "TERM", "xterm-256color");
	if (!env_search(sh->env, "HOME"))
	{
		pw = getpwuid(getuid());
		env_insert(sh, sh->env, "HOME", pw->pw_dir);
	}
	if (!(f = ft_strjoins(env_search(sh->env, "HOME"), HISTFILE)))
		return ;
	env_insert_local(sh, sh->env, "HISTFILE", f);
	shlvl = (env_search(sh->env, "SHLVL"))
		? ft_itoa(ft_atoi(env_search(sh->env, "SHLVL")) + 1)
		: ft_strdup("1");
	env_insert(sh, sh->env, "SHLVL", shlvl);
	if (!(env_search(sh->env, "PWD")) && (path = getcwd(path, PATH_MAX)))
		env_insert(sh, sh->env, "PWD", path);
	ft_strdel(&f);
	ft_strdel(&path);
	ft_strdel(&shlvl);
}

void		env_initialize(t_shell *sh, t_env *env, char **environ)
{
	char		*key;
	char		*value;
	size_t		i;

	i = 0;
	key = NULL;
	value = NULL;
	while (environ && environ[i])
	{
		value = ft_strchrsp(environ[i], '=');
		key = ft_strsub(environ[i], 0,
			ft_strlens(environ[i]) - ft_strlens(value) - 1);
		env_insert(sh, env, key, value);
		(key) ? ft_strdel(&key) : 0;
		i++;
	}
}
