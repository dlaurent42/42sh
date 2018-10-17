/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:20:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 13:48:26 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		env_initialize(t_shell *sh, t_env *env, char **environ)
{
	char		*key;
	char		*value;
	size_t		i;

	i = 0;
	key = NULL;
	value = NULL;
	while (environ && environ[i] && i < ENV_MAX_SIZE)
	{
		value = ft_strchrsp(environ[i], '=');
		key = ft_strsub(environ[i], 0,
			ft_strlens(environ[i]) - ft_strlens(value) - 1);
		env_insert(sh, env, key, value);
		(key) ? ft_strdel(&key) : 0;
		i++;
	}
}
