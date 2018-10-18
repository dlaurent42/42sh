/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ppid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:00:54 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 12:24:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_ppid(t_shell *sh)
{
	char	*ppid;

	if (!(ppid = ft_itoa(getppid())))
		return ;
	if (env_search(sh->env, "PPID") || sh->env->count + 1 < sh->env->size)
		env_insert_local(sh, sh->env, "PPID", ppid);
	ft_strdel(&ppid);
}
