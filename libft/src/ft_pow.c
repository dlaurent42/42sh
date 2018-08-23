/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:55:40 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/03 14:55:41 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_pow(int nb, int power)
{
	int total;

	if (power >= 0)
	{
		total = 1;
		if (power > 0)
			total = nb * ft_pow(nb, power - 1);
	}
	else
		total = 0;
	return (total);
}
