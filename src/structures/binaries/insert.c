/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:11:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/31 16:50:14 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bin_item	*bin_new_item(t_shell *shell, t_bin *bin, char *k, char *v)
{
	t_bin_item	*item;

	if (!(item = (t_bin_item *)ft_memalloc(sizeof(t_bin_item))))
		error_malloc(shell, bin, "t_bin_item");
	item->key = ft_strdups(k);
	item->value = ft_strdups(v);
    return (item);
}

void 				bin_insert(t_shell *shell, t_bin *bin, char *k, char *v)
{
	int			i;
	int			index;
	t_bin_item	*item;
	t_bin_item	*current_item;
	t_bin_item	deleleted_item;

	i = 1;
	deleleted_item.key = NULL;
	deleleted_item.value = NULL;
	item = bin_new_item(shell, bin, k, v);
	index = bin_get_hash(item->key, bin->size, 0);
	current_item = bin->items[index];
	while (current_item)
	{
		if (current_item != &deleleted_item
		&& !ft_strcmp(current_item->key, k))
		{
                bin->items[index] = item;
                return bin_delete_specified_item(current_item);
        }
        index = bin_get_hash(item->key, bin->size, i);
        current_item = bin->items[index];
        i++;
    } 
    bin->items[index] = item;
    bin->count++;
}
