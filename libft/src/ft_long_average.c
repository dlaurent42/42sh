/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_average.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:54:26 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/03 14:54:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_long_average(long *val)
{
	long	i;
	long	length;
	long	sommeprod;

	i = 0;
	if (!(length = sizeof(val) / sizeof(val[0]) + 1))
		return (0);
	sommeprod = 0;
	while (i < length)
	{
		sommeprod += val[i];
		i++;
	}
	return (sommeprod / length);
}
