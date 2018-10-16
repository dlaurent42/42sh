/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_local.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:31:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 19:36:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	env_initialize_localfiles(t_shell *sh)
{
	char		*f;

	if (!(f = ft_strjoins(env_search(sh->env, "HOME"), HISTFILE)))
		return ;
	env_insert_local(sh, sh->env, "HISTFILE", f);
	ft_strdel(&f);
	if (!(f = ft_strjoins(env_search(sh->env, "HOME"), ALIASFILE)))
		return ;
	env_insert_local(sh, sh->env, "ALIASES", f);
	ft_strdel(&f);
}

static void	env_initialize_paths(t_shell *sh)
{
	char		*path;
	t_passwd	*pw;

	path = NULL;
	if (env_search(sh->env, "HOME"))
		return ;
	pw = getpwuid(getuid());
	env_insert(sh, sh->env, "HOME", pw->pw_dir);
	if (!(env_search(sh->env, "PWD")) && (path = getcwd(path, PATH_MAX)))
		env_insert(sh, sh->env, "PWD", path);
	ft_strdel(&path);
}

static void	env_initialize_term(t_shell *sh)
{
	if (!(env_search(sh->env, "TERM")))
		env_insert(sh, sh->env, "TERM", TERM_DEFAULT);
}

static void	env_initialize_shlvl(t_shell *sh)
{
	char		*shlvl;

	shlvl = (env_search(sh->env, "SHLVL"))
		? ft_itoa(ft_atoi(env_search(sh->env, "SHLVL")) + 1)
		: ft_strdup("1");
	env_insert(sh, sh->env, "SHLVL", shlvl);
	ft_strdel(&shlvl);
}

void		env_initialize_local(t_shell *sh)
{
	env_initialize_localfiles(sh);
	env_initialize_paths(sh);
	env_initialize_term(sh);
	env_initialize_shlvl(sh);
}
