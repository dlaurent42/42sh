/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_str_size_base.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:50:09 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/13 20:45:02 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	str_size_base(size_t base_size, unsigned long long nbr)
{
	size_t	size;

	size = 0;
	while (nbr > base_size - 1)
	{
		size++;
		nbr /= base_size;
	}
	return (++size);
}
