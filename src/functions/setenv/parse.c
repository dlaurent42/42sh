/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 17:15:09 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/02 18:20:52 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_setenv_parse(char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg && arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			j = i;
			while (arg[j])
			{
				arg[j] = arg[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	return (arg);
}
