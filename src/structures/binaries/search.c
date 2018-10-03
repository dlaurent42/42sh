/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:15:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 20:16:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_bin_obj	*bin_search(t_bin *bin, const char *key)
{
	int			i;
	int			index;
	t_bin_item	*item;

	i = 1;
	index = bin_get_hash(key, bin->size, 0);
	item = bin->items[index];
	while (item)
	{
		if (item != &bin->del && !ft_strcmps(item->key, key))
			return (item->value);
		index = bin_get_hash(key, bin->size, i);
		item = bin->items[index];
		i++;
	}
	return (NULL);
}
