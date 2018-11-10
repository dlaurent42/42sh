/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:15:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 19:46:32 by dlaurent         ###   ########.fr       */
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
	if ((index = bin_get_hash(key, bin->size, 0)) < 0)
		return (NULL);
	item = bin->items[index];
	while (item)
	{
		if (item != &bin->del && !ft_strcmps(item->key, key))
			return (item->value);
		if ((index = bin_get_hash(key, bin->size, i)) < 0)
			return (NULL);
		item = bin->items[index];
		i++;
	}
	return (NULL);
}
