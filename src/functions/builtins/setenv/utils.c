/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 09:00:04 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 09:00:40 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	sh_setenv_isbin(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
			return (0);
		if (i && arg[i] == '=' && arg[i + 1] && arg[i + 1] == '=' && arg[i + 2])
			return (i + 2);
		i++;
	}
	return (0);
}

int	sh_setenv_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
