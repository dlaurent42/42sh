/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 19:20:04 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 19:33:39 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	env_search_autocompletion_add_item(t_env *env, t_env_item *item)
{
	int		i;

	i = 0;
	while (env->full_env[i])
		i++;
	if (i >= ENV_MAX_SIZE)
		return ;
	env->full_env[i] = ft_strjoins(item->key, "=");
	env->full_env[i] = ft_strjoinf(env->full_env[i], item->value, 1);
}

void		env_search_autocompletion(t_shell *sh, char *key)
{
	int			i;
	long		index;
	t_env		*env;
	t_env_item	*item;

	env = sh->env;
	env_delete_autocompletion_array(env);
	i = 1;
	index = env_get_hash(key, env->size, 0);
	item = env->items[index];
	while (item)
	{
		if (item && item != &env->del
		&& ft_strstartsby(item->key, key))
			env_search_autocompletion_add_item(env, item);
		index = env_get_hash(key, env->size, i);
		item = env->items[index];
		i++;
	}
	ft_sort_wordtab(env->full_env);
}
