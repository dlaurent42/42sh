/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:15:10 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 23:42:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_bin	*bin_new(t_shell *sh, t_env *env)
{
	t_bin	*bin;

	if (!(bin = (t_bin *)ft_memalloc(sizeof(t_bin))))
		error_malloc_bin(sh, NULL, "t_bin structure");
	bin->size = BIN_MAX_SIZE;
	bin->count = 0;
	bin->del.key = NULL;
	bin->del.value = NULL;
	if (!(bin->items = (t_bin_item **)ft_memalloc(sizeof(t_bin_item *)
	* bin->size)))
		error_malloc_bin(sh, bin, "t_bin_items");
	bin_initialize(sh, env, bin);
	return (bin);
}
