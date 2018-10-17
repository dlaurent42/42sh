/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:11:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/17 14:52:19 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_bin_item	*bin_new_item(t_shell *sh, t_bin *bin, t_bin_obj *obj)
{
	t_bin_item	*item;

	if (!(item = (t_bin_item *)ft_memalloc(sizeof(t_bin_item))))
		error_malloc_bin(sh, bin, "t_bin_item structure");
	item->key = obj->name;
	item->value = obj;
	return (item);
}

t_bin_obj			*bin_new_obj(t_shell *sh, char *n, char *p, t_stat st)
{
	t_bin_obj	*obj;

	if (!(obj = (t_bin_obj *)ft_memalloc(sizeof(t_bin_obj))))
		error_malloc_bin(sh, NULL, "t_bin_obj structure");
	obj->name = ft_strdups(n);
	obj->path = ft_strjoins(p, "/");
	obj->path = ft_strjoinf(obj->path, n, 1);
	obj->stats = st;
	return (obj);
}

static void			bin_insert_ready(t_shell *sh, t_bin *bin, t_bin_obj *obj)
{
	if (!bin->bin_auto)
		sh_add_builtins_to_auto_comp(sh, bin);
	bin_gen_list_for_auto_comp(sh, bin, obj->name);
}

void				bin_insert(t_shell *sh, t_bin *bin, t_bin_obj *obj)
{
	int			i;
	long		index;
	t_bin_item	*item;
	t_bin_item	*curr_item;

	i = 1;
	item = bin_new_item(sh, bin, obj);
	index = bin_get_hash(item->key, bin->size, 0);
	curr_item = bin->items[index];
	while (curr_item)
	{
		if (curr_item != &bin->del && !ft_strcmps(curr_item->key, obj->name))
		{
			bin->items[index] = item;
			bin_insert_ready(sh, bin, obj);
			return (bin_delete_specified_item(curr_item));
		}
		index = bin_get_hash(item->key, bin->size, i++);
		curr_item = bin->items[index];
	}
	if (bin->count + 1 >= bin->size)
		return (bin_delete_specified_item(item));
	bin_insert_ready(sh, bin, obj);
	bin->items[index] = item;
	bin->count++;
}
