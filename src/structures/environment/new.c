/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:36:42 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 00:07:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(t_shell *shell, char **environ)
{
	t_env	*env;

	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		error_malloc_env(shell, NULL, "t_env structure");
	env->size = ENV_MAX_SIZE;
	env->count = 0;
	if (!(env->items = (t_env_item **)ft_memalloc(sizeof(t_env_item *)
	* env->size)))
		error_malloc_env(shell, env, "env_items");
	env_initialize(shell, env, environ);
	return (env);
}
