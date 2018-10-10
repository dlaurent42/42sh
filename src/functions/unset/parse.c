/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 14:36:30 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/10 14:36:36 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_unset_parse(char *arg)
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
