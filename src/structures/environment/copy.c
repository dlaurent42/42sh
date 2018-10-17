/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 11:39:23 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 15:38:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_env	*env_copy_items(t_shell *sh, t_env *src, t_env *env)
{
	char		*key;
	char		*value;
	size_t		i;

	i = 0;
	key = NULL;
	value = NULL;
	while (src->environment[i] && i < env->size)
	{
		value = ft_strchrsp(src->environment[i], '=');
		key = ft_strsub(src->environment[i], 0,
			ft_strlens(src->environment[i]) - ft_strlens(value) - 1);
		env_insert(sh, env, key, value);
		(key) ? ft_strdel(&key) : 0;
		i++;
	}
	return (env);
}

t_env			*env_copy(t_shell *sh, t_env *src)
{
	t_env		*env;

	if (!sh || !src)
		return (NULL);
	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		error_malloc_env(sh, NULL, "t_env structure");
	env->size = ENV_MAX_SIZE;
	env->count = 0;
	env->del.key = NULL;
	env->del.value = NULL;
	if (!(env->items = (t_env_item **)ft_memalloc(sizeof(t_env_item *)
	* env->size)))
		error_malloc_env(sh, env, "env_items");
	env->count = src->count;
	return (env_copy_items(sh, src, env));
}
