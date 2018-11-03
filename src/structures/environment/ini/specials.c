/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specials.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:07:41 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/03 20:14:09 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_env_init_specials(t_shell *sh, char *name)
{
	char	*pid;

	pid = ft_itoa(getpid());
	if (!env_search(sh->env, "@") && sh->env->count + 1 < sh->env->size)
		env_insert_protected(sh, sh->env, "@", "");
	if (!env_search(sh->env, "*") && sh->env->count + 1 < sh->env->size)
		env_insert_protected(sh, sh->env, "*", "");
	if (!env_search(sh->env, "#") && sh->env->count + 1 < sh->env->size)
		env_insert_protected(sh, sh->env, "#", "0");
	if (!env_search(sh->env, "?") && sh->env->count + 1 < sh->env->size)
		env_insert_protected(sh, sh->env, "?", "0");
	if (!env_search(sh->env, "!") && sh->env->count + 1 < sh->env->size)
		env_insert_protected(sh, sh->env, "!", "0");
	if (!env_search(sh->env, "-") && sh->env->count + 1 < sh->env->size)
		env_insert_protected(sh, sh->env, "-", "no option :(");
	if (!env_search(sh->env, "$") && sh->env->count + 1 < sh->env->size)
		(pid)
			? env_insert_protected(sh, sh->env, "$", pid)
			: env_insert_protected(sh, sh->env, "$", "");
	if (!env_search(sh->env, "0") && sh->env->count + 1 < sh->env->size)
		env_insert_protected(sh, sh->env, "0", name);
	ft_strdel(&pid);
}
