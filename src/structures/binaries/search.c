/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:15:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/27 22:49:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_bin_obj	*bin_search(t_bin *bin, const char *key)
{
	int			i;
	long		index;
	t_bin_item	*item;

	i = 1;
	if (!bin)
		return (NULL);
	ft_printf("Looking for key: %s\n", key);
	ft_printf("Bin size is %d\n", bin->size);
	index = bin_get_hash(key, bin->size, 0);
	ft_printf("Bin index is %d\n", index);
	item = bin->items[index];
	while (item)
	{
		ft_printf("... key is %s\n", item->key);
		if (item != &bin->del && !ft_strcmps(item->key, key))
			return (item->value);
		index = bin_get_hash(key, bin->size, i);
		item = bin->items[index];
		i++;
	}
	return (NULL);
}
