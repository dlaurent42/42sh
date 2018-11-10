/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:15:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/10 19:25:25 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	bin_has_unicode(const char *k)
{
	int		i;

	i = 0;
	if (!k)
		return (FALSE);
	while (k[i])
	{
		if (k[i] < 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bin_obj	*bin_search(t_bin *bin, const char *key)
{
	int			i;
	long		index;
	t_bin_item	*item;

	i = 1;
	if (!bin || bin_has_unicode(key))
		return (NULL);
	if ((index = bin_get_hash(key, bin->size, 0)) < 0)
		return (NULL);
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
