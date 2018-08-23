/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:54:23 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/03 15:05:42 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size_of_string(int n)
{
	size_t			size;
	unsigned int	unsigned_n;

	size = 0;
	if (n < 0)
	{
		size++;
		unsigned_n = n * (-1);
	}
	else
		unsigned_n = n;
	while (unsigned_n > 9)
	{
		size++;
		unsigned_n /= 10;
	}
	return (++size);
}

char			*ft_itoa(int n)
{
	char			*s;
	size_t			index;
	unsigned int	unsigned_n;

	index = get_size_of_string(n);
	if (!(s = ft_strnew(sizeof(char) * index)))
		return (NULL);
	if (n < 0)
	{
		s[0] = '-';
		unsigned_n = n * (-1);
	}
	else
		unsigned_n = n;
	s[index] = '\0';
	while (unsigned_n > 9)
	{
		s[--index] = unsigned_n % 10 + 48;
		unsigned_n /= 10;
	}
	s[--index] = unsigned_n + 48;
	return (s);
}
