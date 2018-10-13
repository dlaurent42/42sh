/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:10:03 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/13 18:39:18 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_env_item	*env_new_item(t_shell *sh, t_env *env, char *k, char *v)
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

void		env_insert_item_into_array(t_env *env, char *k, char *v)
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

void		env_insert(t_shell *sh, t_env *env, char *k, char *v)
{
	int			i;
	int			index;
	t_env_item	*item;
	t_env_item	*curr_item;

	i = 1;
	env_insert_item_into_array(env, k, v);
	item = env_new_item(sh, env, k, v);
	index = env_get_hash(item->key, env->size, 0);
	curr_item = env->items[index];
	while (curr_item)
	{
		if (curr_item != &env->del && !ft_strcmps(curr_item->key, k))
		{
			env->items[index] = item;
			return (env_delete_specified_item(curr_item));
		}
		index = env_get_hash(item->key, env->size, i++);
		curr_item = env->items[index];
	}
	env->items[index] = item;
	env->count++;
}

void		env_insert_local(t_shell *sh, t_env *env, char *k, char *v)
{
	int			i;
	int			index;
	t_env_item	*item;
	t_env_item	*curr_item;

	i = 1;
	item = env_new_item(sh, env, k, v);
	item->local = TRUE;
	index = env_get_hash(item->key, env->size, 0);
	curr_item = env->items[index];
	while (curr_item)
	{
		if (curr_item != &env->del && !ft_strcmps(curr_item->key, k))
		{
			env->items[index] = item;
			return (env_delete_specified_item(curr_item));
		}
		index = env_get_hash(item->key, env->size, i++);
		curr_item = env->items[index];
	}
	env->items[index] = item;
	env->count++;
}
