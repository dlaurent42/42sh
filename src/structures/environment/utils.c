/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:50:42 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 13:50:54 by dlaurent         ###   ########.fr       */
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
