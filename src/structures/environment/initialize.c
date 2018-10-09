/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:20:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 15:04:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	env_initialize_local(t_shell *sh)
{
	char	*tmp;

	if (!sh->local_env)
		return ;
	if (!(tmp = env_search(sh->env, "HOME")))
		return ;
	if (!(tmp = ft_strjoins(tmp, "/")))
		return ;
	if (!(tmp = ft_strjoinf(tmp, HISTFILE, 1)))
		return ;
	env_insert(sh, sh->local_env, "HISTFILE", tmp);
	ft_strdel(&tmp);
}

void	env_initialize(t_shell *sh, t_env *env, char **environ)
{
	char		*left;
	char		*right;
	size_t		i;

	i = 0;
	left = NULL;
	right = NULL;
	while (environ && environ[i])
	{
		right = ft_strchrsp(environ[i], '=');
		left = ft_strsub(environ[i], 0,
			ft_strlens(environ[i]) - ft_strlens(right) - 1);
		env_insert(sh, env, left, right);
		(left) ? ft_strdel(&left) : 0;
		i++;
	}
}
