/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 21:05:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 21:06:45 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_env_init_shell(t_shell *sh, char *path)
{
	if (!env_search(sh->env, "SHELL") && sh->env->count + 1 >= sh->env->size)
		return ;
	env_insert(sh, sh->env, "SHELL", path);
}
