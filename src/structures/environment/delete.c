/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:01:59 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 00:04:41 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		env_delete_specified_item(t_env_item *item)
{
	if (item->key)
		ft_strdel(&item->key);
	if (item->value)
		ft_strdel(&item->value);
	free(item);
}

void		env_delete_item(t_env *env, const char *key)
{
	int			i;
	int			index;
	t_env_item	*item;
	t_env_item	deleleted_item;

	i = 1;
	deleleted_item.key = NULL;
	deleleted_item.value = NULL;
	index = env_get_hash(key, env->size, 0);
	item = env->items[index];
	while (item)
	{
		if (item != &deleleted_item && !ft_strcmp(item->key, key))
		{
			env_delete_specified_item(item);
			env->items[index] = &deleleted_item;
		}
		index = env_get_hash(key, env->size, i++);
		item = env->items[index];
	}
	env->count--;
}

void		env_delete(t_env *env)
{
	size_t		i;
	t_env_item	*item;

	i = 0;
	if (!env)
		return ;
	while (i < env->size)
	{
		item = env->items[i];
		if (item)
			env_delete_specified_item(item);
		i++;
	}
	free(env->items);
	free(env);
}
