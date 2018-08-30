/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:36:42 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/30 19:12:21 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(t_shell *shell)
{
	t_env	*env;
	
	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		error_malloc(shell, NULL, "t_env");
	env->size = ENV_MAX_SIZE;
    env->count = 0;
	if (!(env->items = (t_env_item **)ft_memalloc(sizeof(t_env_item *) * env->size)))
		error_malloc(shell, env, "t_env_items");;
    return (env);
}