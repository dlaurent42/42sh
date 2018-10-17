/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:10:46 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 14:54:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	bin_hash(const char *s, const int a, const int m)
{
	long	hash;
	size_t	i;
	size_t	len;

	i = 0;
	hash = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		hash += (long)ft_pow(a, len - (i + 1)) * s[i];
		hash %= m;
		i++;
	}
	return ((int)hash);
}

long		bin_get_hash(const char *s, const int buckets, const int attempt)
{
	int	hash_a;
	int	hash_b;

	hash_a = bin_hash(s, BIN_PRIME_1, buckets);
	hash_b = bin_hash(s, BIN_PRIME_2, buckets);
	return ((hash_a + (attempt * (hash_b + 1))) % buckets);
}
