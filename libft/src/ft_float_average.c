/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_float_average.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:53:21 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/03 14:53:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_float_average(float *val)
{
	long	i;
	float	length;
	float	sommeprod;

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
