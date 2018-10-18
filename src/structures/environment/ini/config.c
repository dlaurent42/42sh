/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:06:10 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 11:19:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_config(t_shell *sh)
{
	char		*file;
	char		*home;

	if (env_search(sh->env, "CONFIG") || sh->env->count + 1 >= sh->env->size)
		return ;
	if (!(home = env_search(sh->env, "HOME")))
		return ;
	if (!(file = ft_strjoins(home, CONFIGFILE)))
		return ;
	env_insert_local(sh, sh->env, "CONFIG", file);
}
