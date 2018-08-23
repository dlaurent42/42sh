/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_average.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:53:37 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/03 14:53:38 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_int_average(int *val)
{
	int		i;
	int		length;
	int		sommeprod;

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
