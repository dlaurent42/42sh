/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:36:42 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/01 14:35:25 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env	*env_new(t_shell *sh, char **environ)
{
	t_env	*env;

	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		error_malloc_env(sh, NULL, "t_env structure");
	env->size = ENV_MAX_SIZE;
	env->count = 0;
	env->del.key = NULL;
	env->del.value = NULL;
	if (!(env->items = (t_env_item **)ft_memalloc(sizeof(t_env_item *)
	* env->size)))
		error_malloc_env(sh, env, "env_items");
	env_initialize(sh, env, environ);
	return (env);
}
