/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:20:43 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/10 14:42:03 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_export_display(t_shell *sh, bool exportable)
{
	int		i;

	i = 0;
	if (!sh->env->environment[0])
		return (0);
	while (sh->env->environment[i])
	{
		(exportable) ? ft_putstr("export ") : 0;
		ft_putendl(sh->env->environment[i]);
		i++;
	}
	return (0);
}
