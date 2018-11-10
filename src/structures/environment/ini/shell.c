/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:05:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 12:01:24 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_shell(t_shell *sh, char *path)
{
	char	*new_name;

	new_name = realpath(path, NULL);
	if (!env_search(sh->env, "SHELL") && sh->env->count + 1 >= sh->env->size)
		return ;
	env_insert(sh, sh->env, "SHELL", new_name);
	ft_strdel(&new_name);
}
