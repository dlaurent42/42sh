/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:55:59 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/03 14:56:00 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	unsigned int unsigned_n;

	if (n < 0)
	{
		ft_putchar('-');
		unsigned_n = n * (-1);
	}
	else
		unsigned_n = n;
	if (unsigned_n > 9)
		ft_putnbr(unsigned_n / 10);
	ft_putchar(unsigned_n % 10 + 48);
}
