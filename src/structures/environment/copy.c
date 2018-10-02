/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 11:39:23 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 11:44:48 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_env	*env_copy_items(t_shell *sh, t_env *env)
{
	char		*left;
	char		*right;
	size_t		i;

	i = 0;
	left = NULL;
	right = NULL;
	while (sh->env->environment[i])
	{
		right = ft_strchrsp(sh->env->environment[i], '=');
		left = ft_strsub(sh->env->environment[i], 0,
			ft_strlens(sh->env->environment[i]) - ft_strlens(right) - 1);
		env_insert(sh, env, left, right);
		(left) ? ft_strdel(&left) : 0;
		i++;
	}
	return (env);
}

t_env			*env_copy(t_shell *sh)
{
	t_env		*env;

	if (!sh->env)
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
	return (env_copy_items(sh, env));
}
