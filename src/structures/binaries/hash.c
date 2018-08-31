/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:10:46 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/31 16:11:17 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int 	bin_hash(const char *s, const int a, const int m)
{
	long	hash;
	size_t	i;
	size_t	length;

	i = 0;
	hash = 0;
	length = ft_strlen(s);
	while (i < length)
	{
		hash += (long)ft_pow(a, length - (i + 1)) * s[i];
		hash %= m;
		i++;
	}
    return ((int)hash);
}

int 		bin_get_hash(const char *s, const int num_buckets, const int attempt)
{
    int	hash_a;
	int	hash_b;

	hash_a = bin_hash(s, BIN_PRIME_1, num_buckets);
	hash_b = bin_hash(s, BIN_PRIME_2, num_buckets);
    return ((hash_a + (attempt * (hash_b + 1))) % num_buckets);
}
