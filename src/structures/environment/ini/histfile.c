/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   histfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:06:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 11:18:32 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_histfile(t_shell *sh)
{
	char		*file;
	char		*home;

	if (env_search(sh->env, "HISTFILE") || sh->env->count + 1 >= sh->env->size)
		return ;
	if (!(home = env_search(sh->env, "HOME")))
		return ;
	if (!(file = ft_strjoins(home, HISTFILE)))
		return ;
	env_insert_local(sh, sh->env, "HISTFILE", file);
}
