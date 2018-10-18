/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_local.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:31:19 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 11:19:18 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
