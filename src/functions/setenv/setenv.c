/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 01:11:14 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/01 14:16:39 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_setenv(t_shell *sh, char *args)
{
	int		pos;
	char	*key;
	char	*value;

	pos = 0;
	key = NULL;
	value = NULL;
	if (!args)
		return (-1);
	while (args[pos] && args[pos] != '=')
		pos++;
	if (pos == 0)
		return (-1);
	value = ft_strdups(args + pos + 1);
	args[pos] = '\0';
	if (!env_search(sh->env, args) && sh->env->count + 1 >= sh->env->size)
	{
		ft_strdel(&value);
		return (-1);
	}
	env_insert(sh, sh->env, args, value);
	ft_strdel(&value);
	return (0);
}
