/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:01:59 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 14:52:02 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		bin_delete_specified_item(t_bin_item *item)
{
	if (item->value)
	{
		ft_strdel(&item->value->name);
		ft_strdel(&item->value->path);
		free(item->value);
	}
	free(item);
}

void		bin_delete_item(t_bin *bin, const char *key)
{
	int			i;
	long		index;
	t_bin_item	*item;

	i = 1;
	index = bin_get_hash(key, bin->size, 0);
	item = bin->items[index];
	while (item)
	{
		if (item != &bin->del && !ft_strcmps(item->key, key))
		{
			bin_delete_specified_item(item);
			bin->items[index] = &bin->del;
		}
		index = bin_get_hash(key, bin->size, i);
		item = bin->items[index];
		i++;
	}
	bin->count--;
}

void		bin_delete(t_bin *bin)
{
	size_t		i;
	t_bin_item	*item;
	t_bin_auto	*bin_auto;

	i = 0;
	if (!bin)
		return ;
	while (bin->bin_auto)
	{
		bin_auto = bin->bin_auto->next;
		free(bin->bin_auto->name);
		free(bin->bin_auto);
		bin->bin_auto = bin_auto;
	}
	while (i < bin->size)
	{
		item = bin->items[i];
		if (item)
			bin_delete_specified_item(item);
		i++;
	}
	free(bin->items);
	free(bin);
}
