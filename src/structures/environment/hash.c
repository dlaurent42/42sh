/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:18:04 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 16:34:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	env_hash(const char *s, const int a, const int m)
{
	long	hash;
	size_t	i;
	size_t	len;

	i = 0;
	hash = 0;
	len = ft_strlens(s);
	while (i < len)
	{
		hash += (long)ft_pow(a, len - (i + 1)) * s[i];
		hash %= m;
		i++;
	}
	return ((int)hash);
}

long		env_get_hash(const char *s, const int buckets, const int attempt)
{
	int	hash_a;
	int	hash_b;

	hash_a = env_hash(s, ENV_PRIME_1, buckets);
	hash_b = env_hash(s, ENV_PRIME_2, buckets);
	return ((hash_a + (attempt * (hash_b + 1))) % buckets);
}
