/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:18:54 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 16:48:34 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_alias_display(t_env *env, bool exportable)
{
	int		i;

	i = 0;
	if (!env->environment[0])
		return (0);
	while (env->environment[i])
	{
		(exportable) ? ft_putstr("alias ") : 0;
		ft_putendl(env->environment[i]);
		i++;
	}
	return (0);
}
