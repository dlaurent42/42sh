/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 12:01:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 12:22:56 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_ps(t_shell *sh)
{
	if (!env_search(sh->env, "PS1") && sh->env->count + 1 < sh->env->size)
		env_insert_local(sh, sh->env, "PS1", "");
	if (!env_search(sh->env, "PS2") && sh->env->count + 1 < sh->env->size)
		env_insert_local(sh, sh->env, "PS2", MULT_PROMPT);
	if (!env_search(sh->env, "PS3") && sh->env->count + 1 < sh->env->size)
		env_insert_local(sh, sh->env, "PS3", "");
	if (!env_search(sh->env, "PS4") && sh->env->count + 1 < sh->env->size)
		env_insert_local(sh, sh->env, "PS4", "+ ");
}
