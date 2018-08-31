/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:10:03 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 00:08:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env_item	*env_new_item(t_shell *shell, t_env *env, char *k, char *v)
{
	t_env_item	*item;

	if (!(item = (t_env_item *)ft_memalloc(sizeof(t_env_item))))
		error_malloc_env(shell, env, "t_env_item");
	item->key = ft_strdups(k);
	item->value = ft_strdups(v);
	return (item);
}

void				env_insert(t_shell *shell, t_env *env, char *k, char *v)
{
	int			i;
	int			index;
	t_env_item	*item;
	t_env_item	*current_item;
	t_env_item	deleleted_item;

	i = 1;
	deleleted_item.key = NULL;
	deleleted_item.value = NULL;
	item = env_new_item(shell, env, k, v);
	index = env_get_hash(item->key, env->size, 0);
	current_item = env->items[index];
	while (current_item)
	{
		if (current_item != &deleleted_item
		&& !ft_strcmp(current_item->key, k))
		{
			env->items[index] = item;
			return (env_delete_specified_item(current_item));
		}
		index = env_get_hash(item->key, env->size, i++);
		current_item = env->items[index];
	}
	env->items[index] = item;
	env->count++;
}
