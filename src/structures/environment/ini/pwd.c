/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:07:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 11:10:36 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_pwd(t_shell *sh)
{
	char		*path;

	path = NULL;
	if (!(env_search(sh->env, "PWD")) && sh->env->count + 1 < sh->env->size
	&& (path = getcwd(path, PATH_MAX)))
		env_insert(sh, sh->env, "PWD", path);
	ft_strdel(&path);
}
