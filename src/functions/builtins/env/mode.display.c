/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:11:17 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/13 00:30:07 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_env_print(t_env *env)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	while (env->environment[i])
	{
		j = 0;
		key = ft_strdups(env->environment[i]);
		while (key[j])
		{
			if (key[j] == '=')
				key[j] = '\0';
			j++;
		}
		if (env_search_public(env, key))
			ft_putendl(env->environment[i]);
		ft_strdel(&key);
		i++;
	}
	env_delete(env);
	return (0);
}
