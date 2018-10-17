/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:01:59 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 19:34:28 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		env_delete_autocompletion_array(t_env *env)
{
	int		i;

	i = 0;
	while (env->full_env[i])
	{
		ft_strdel(&env->full_env[i]);
		i++;
	}
}

char		env_delete_item_from_array(t_env *env, const char *key)
{
	char			del;
	unsigned char	i;
	unsigned char	j;

	i = 0;
	del = FALSE;
	while (env->environment[i])
	{
		j = 0;
		while (env->environment[i][j] && key[j]
		&& env->environment[i][j] == key[j])
			j++;
		if (!key[j] && env->environment[i][j] == '=')
		{
			del = TRUE;
			ft_strdel(&env->environment[i]);
			break ;
		}
		i++;
	}
	i--;
	while (++i < (int)env->count)
		env->environment[i] = env->environment[i + 1];
	return (del);
}

void		env_delete_specified_item(t_env_item *item)
{
	free(item->key);
	free(item->value);
	free(item);
}

void		env_delete_item(t_env *env, const char *key)
{
	int			i;
	long		index;
	t_env_item	*item;

	i = 1;
	env_delete_item_from_array(env, key);
	index = env_get_hash(key, env->size, 0);
	item = env->items[index];
	while (item)
	{
		if (item != &env->del && !ft_strcmps(item->key, key))
		{
			env_delete_specified_item(item);
			env->items[index] = &env->del;
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
		if (item && item != &env->del)
			env_delete_specified_item(item);
		i++;
	}
	i = 0;
	while (env->environment[i])
	{
		ft_strdel(&env->environment[i]);
		i++;
	}
	env_delete_autocompletion_array(env);
	free(env->items);
	free(env);
}
