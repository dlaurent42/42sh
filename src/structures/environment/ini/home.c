/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:07:03 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 11:12:07 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_home(t_shell *sh)
{
	t_passwd	*pw;

	if (env_search(sh->env, "HOME") || sh->env->count + 1 >= sh->env->size)
		return ;
	pw = getpwuid(getuid());
	env_insert(sh, sh->env, "HOME", pw->pw_dir);
}
