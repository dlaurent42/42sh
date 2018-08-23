/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_ulltoa_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 20:50:21 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/13 20:45:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ulltoa_base(char *base, unsigned long long nbr)
{
	char	*str;
	size_t	base_size;
	size_t	size;

	base_size = ft_strlen(base);
	size = str_size_base(base_size, nbr);
	if (!(str = ft_strnew(sizeof(char) * size)))
		return (NULL);
	while (nbr > base_size - 1)
	{
		str[--size] = base[nbr % base_size];
		nbr /= base_size;
	}
	str[--size] = base[nbr];
	return (str);
}
