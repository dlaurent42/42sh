/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inject.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 10:59:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:48:59 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	lexer_inject_cpy(char *str, char *injection, int i)
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

char	*lexer_inject_dup(char *str, char *injection, int i)
{
	int		j;
	char	*left;
	char	*right;

	j = 0;
	if (!str)
		return (ft_strdups(injection));
	right = ft_strdups(str + i);
	left = ft_strsub(str, 0, i);
	ft_strdel(&str);
	str = ft_strjoinf(left, injection, 1);
	str = ft_strjoinf(str, right, 3);
	return (str);
}
