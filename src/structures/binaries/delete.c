/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 18:01:59 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 01:14:59 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		bin_delete_specified_item(t_bin_item *item)
{
	if (item->value)
	{
		ft_strdel(&item->value->name);
		free(item->value);
	}
	free(item);
}

void		bin_delete_item(t_bin *bin, const char *key)
{
	int			i;
	int			index;
	t_bin_item	*item;
	t_bin_item	deleleted_item;

	i = 1;
	deleleted_item.key = NULL;
	deleleted_item.value = NULL;
	index = bin_get_hash(key, bin->size, 0);
	item = bin->items[index];
	while (item)
	{
		if (item != &deleleted_item && !ft_strcmp(item->key, key))
		{
			bin_delete_specified_item(item);
			bin->items[index] = &deleleted_item;
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

	i = 0;
	if (!bin)
		return ;
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
