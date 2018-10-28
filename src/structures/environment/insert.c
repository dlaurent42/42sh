/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:10:03 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/28 18:42:55 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_env_item	*env_new_item(t_shell *sh, t_env *env, char *k, char *v)
{
	t_env_item	*item;

	if (!(item = (t_env_item *)ft_memalloc(sizeof(t_env_item))))
		error_malloc_env(sh, env, "t_env_item");
	if (!(item->key = ft_strdups(k)))
	{
		free(item);
		error_malloc_env(sh, env, "t_env_item");
	}
	item->value = ft_strdups(v);
	return (item);
}

void				env_insert_item_into_array(t_env *env, char *k, char *v)
{
	char			*var;
	unsigned char	i;

	i = 0;
	var = ft_strjoins(k, "=");
	var = ft_strjoinf(var, v, 1);
	while (env->environment[i])
	{
		if (ft_strcmps(env->environment[i], var) == 0)
			return (ft_strdel(&var));
		i++;
	}
	i -= (env_delete_item_from_array(env, k)) ? 1 : 0;
	env->environment[i] = ft_strdupf(var);
}

void				env_insert(t_shell *sh, t_env *env, char *k, char *v)
{
	int			i;
	long		index;
	t_env_item	*item;
	t_env_item	*curr_item;

	i = 1;
	if (!env_key_is_ok(k))
		return ;
	item = env_new_item(sh, env, k, v);
	index = env_get_hash(item->key, env->size, 0);
	while ((curr_item = env->items[index]))
	{
		if (curr_item != &env->del && !ft_strcmps(curr_item->key, k))
		{
			env->items[index] = item;
			env_insert_item_into_array(env, k, v);
			return (env_delete_specified_item(curr_item));
		}
		index = env_get_hash(item->key, env->size, i++);
	}
	if (env->count + 1 >= env->size)
		return (env_delete_specified_item(item));
	env_insert_item_into_array(env, k, v);
	env->items[index] = item;
	env->count++;
}

void				env_insert_local(t_shell *sh, t_env *env, char *k, char *v)
{
	int			i;
	long		index;
	t_env_item	*item;
	t_env_item	*curr_item;

	i = 1;
	if (!env_key_is_ok(k))
		return ;
	item = env_new_item(sh, env, k, v);
	item->local = TRUE;
	index = env_get_hash(item->key, env->size, 0);
	while ((curr_item = env->items[index]))
	{
		if (curr_item != &env->del && !ft_strcmps(curr_item->key, k))
		{
			env->items[index] = item;
			return (env_delete_specified_item(curr_item));
		}
		index = env_get_hash(item->key, env->size, i++);
	}
	if (env->count + 1 >= env->size)
		return (env_delete_specified_item(item));
	env->items[index] = item;
	env->count++;
}

void				env_insert_protected(
	t_shell *sh, t_env *env, char *k, char *v)
{
	int			i;
	long		index;
	t_env_item	*item;
	t_env_item	*curr_item;

	i = 1;
	if (!env_key_is_protected(k))
		return ;
	item = env_new_item(sh, env, k, v);
	item->local = TRUE;
	index = env_get_hash(item->key, env->size, 0);
	while ((curr_item = env->items[index]))
	{
		if (curr_item != &env->del && !ft_strcmps(curr_item->key, k))
		{
			env->items[index] = item;
			return (env_delete_specified_item(curr_item));
		}
		index = env_get_hash(item->key, env->size, i++);
	}
	if (env->count + 1 >= env->size)
		return (env_delete_specified_item(item));
	env->items[index] = item;
	env->count++;
}
