/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_average.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:51:13 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/03 14:51:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_double_average(double *val)
{
	long	i;
	double	length;
	double	sommeprod;

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
