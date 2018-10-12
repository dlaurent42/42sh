/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_public.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 16:10:57 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 23:01:06 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*env_search_public(t_env *env, const char *key)
{
	int			i;
	int			index;
	t_env_item	*item;

	i = 1;
	index = env_get_hash(key, env->size, 0);
	item = env->items[index];
	while (item)
	{
		if (item && item != &env->del && !item->local
		&& !ft_strcmps(item->key, key))
			return (item->value);
		index = env_get_hash(key, env->size, i);
		item = env->items[index];
		i++;
	}
	return (NULL);
}
