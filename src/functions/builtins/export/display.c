/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:20:43 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/11 15:52:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_export_display(t_env *env, bool exportable)
{
	int		i;

	i = 0;
	if (!env->environment[0])
		return (0);
	while (env->environment[i])
	{
		(exportable) ? ft_putstr("export ") : 0;
		ft_putendl(env->environment[i]);
		i++;
	}
	return (0);
}
