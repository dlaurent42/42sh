/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:07:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 12:50:02 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_shlvl(t_shell *sh)
{
	char		*shlvl;

	shlvl = NULL;
	if ((shlvl = env_search(sh->env, "SHLVL")) && ft_isint(shlvl))
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		env_insert(sh, sh->env, "SHLVL", shlvl);
	}
	else if ((shlvl = ft_strdup("1")))
	{
		if (sh->env->count + 1 < sh->env->size)
			env_insert(sh, sh->env, "SHLVL", shlvl);
	}
	ft_strdel(&shlvl);
}
