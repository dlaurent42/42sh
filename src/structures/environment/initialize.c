/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:20:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 17:10:46 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_initialize_local(t_shell *sh)
{
	char	*tmp;

	if (!sh->env)
		return ;
	if (!(tmp = env_search(sh->env, "HOME")))
		return ;
	if (!(tmp = ft_strjoins(tmp, HISTFILE)))
		return ;
	env_insert_local(sh, sh->env, "HISTFILE", tmp);
	ft_strdel(&tmp);
}

void	env_initialize(t_shell *sh, t_env *env, char **environ)
{
	char		*key;
	char		*value;
	size_t		i;

	i = 0;
	key = NULL;
	value = NULL;
	while (environ && environ[i])
	{
		value = ft_strchrsp(environ[i], '=');
		key = ft_strsub(environ[i], 0,
			ft_strlens(environ[i]) - ft_strlens(value) - 1);
		env_insert(sh, env, key, value);
		(key) ? ft_strdel(&key) : 0;
		i++;
	}
}
