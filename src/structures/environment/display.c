/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 21:06:45 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 20:29:18 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool	env_display(t_env *env, char *keyword)
{
	int		i;

	i = 0;
	if (!env->environment[0])
		return (0);
	while (env->environment[i])
	{
		ft_putstr(keyword);
		ft_putendl(env->environment[i]);
		i++;
	}
	return (0);
}
