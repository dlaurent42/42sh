/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inject.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 10:59:06 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/20 17:51:49 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_glob_inject(char *str, char *injection, int i)
{
	int		j;
	char	*left;
	char	*right;

	j = 0;
	right = ft_strdups(str + i);
	left = ft_strsub(str, 0, i);
	ft_strdel(&str);
	str = ft_strjoinf(left, injection, 1);
	str = ft_strjoinf(str, right, 3);
	return (str);
}
