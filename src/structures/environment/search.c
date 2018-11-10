/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 16:10:57 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 19:46:22 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*env_search_public(t_env *env, const char *key)
{
	int			i;
	long		index;
	t_env_item	*item;

	i = 1;
	if ((index = env_get_hash(key, env->size, 0)) < 0)
		return (NULL);
	item = env->items[index];
	while (item)
	{
		if (item && item != &env->del && !item->local
		&& !ft_strcmps(item->key, key))
			return (item->value);
		if ((index = env_get_hash(key, env->size, i)) < 0)
			return (NULL);
		item = env->items[index];
		i++;
	}
	return (NULL);
}

char		*env_search_local(t_env *env, const char *key)
{
	int			i;
	long		index;
	t_env_item	*item;

	i = 1;
	if ((index = env_get_hash(key, env->size, 0)) < 0)
		return (NULL);
	item = env->items[index];
	while (item)
	{
		if (item && item != &env->del && item->local
		&& !ft_strcmps(item->key, key))
			return (item->value);
		if ((index = env_get_hash(key, env->size, i)) < 0)
			return (NULL);
		item = env->items[index];
		i++;
	}
	return (NULL);
}

char		*env_search(t_env *env, const char *key)
{
	int			i;
	long		index;
	t_env_item	*item;

	i = 1;
	if ((index = env_get_hash(key, env->size, 0)) < 0)
		return (NULL);
	item = env->items[index];
	while (item)
	{
		if (item && item != &env->del
		&& !ft_strcmps(item->key, key))
			return (item->value);
		if ((index = env_get_hash(key, env->size, i)) < 0)
			return (NULL);
		item = env->items[index];
		i++;
	}
	return (NULL);
}
