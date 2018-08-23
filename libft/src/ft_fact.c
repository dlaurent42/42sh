/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fact.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:53:11 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/03 15:07:34 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fact(int nb)
{
	int	result;

	result = 0;
	if (nb >= 0 && nb <= 12)
	{
		result = 1;
		if (nb > 1)
			result = nb * ft_fact(nb - 1);
	}
	else
		return (0);
	return (result);
}
