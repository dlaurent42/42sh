/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:09:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/25 19:14:28 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_environment(t_env *env)
{
	t_env	*tmp;

	tmp = NULL;
	if (!env)
		return ;
	env = env->head;
	while (env)
	{
		tmp = env->next;
		if (env->key)
			ft_strdel(&env->key);
		if (env->value)
			ft_strdel(&env->value);
		free(env);
		env = tmp;
	}	
}
