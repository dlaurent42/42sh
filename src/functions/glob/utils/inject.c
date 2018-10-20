/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inject.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 10:59:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/20 16:54:09 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_glob_inject(char *str, char *injection, int i)
{
	int		j;
	char	*left;
	char	*right;

	j = 0;
	ft_printf("injection received: [%s]\n", str);
	right = ft_strdups(str + i);
	left = ft_strsub(str, 0, i);
	ft_strdel(&str);
	str = ft_strjoinf(left, injection, 1);
	str = ft_strjoinf(str, right, 3);
	ft_printf("injection output: [%s]\n", str);
	return (str);
}
