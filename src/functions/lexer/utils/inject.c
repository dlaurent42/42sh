/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inject.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 10:59:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 16:58:05 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_command_inject(char *str, char *injection, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	tmp = ft_strdups(str + i);
	while (injection[j] && i < ARG_MAX + 1)
	{
		str[i] = injection[j];
		i++;
		j++;
	}
	j = 0;
	while (tmp[j] && i < ARG_MAX + 1)
	{
		str[i] = tmp[j];
		i++;
		j++;
	}
	ft_strdel(&tmp);
}
