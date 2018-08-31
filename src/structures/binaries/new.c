/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:15:10 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/31 16:15:39 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bin	*bin_new(t_shell *shell)
{
	t_bin	*bin;
	
	if (!(bin = (t_bin *)ft_memalloc(sizeof(t_bin))))
		error_malloc(shell, NULL, "t_bin");
	bin->size = BIN_MAX_SIZE;
    bin->count = 0;
	if (!(bin->items = (t_bin_item **)ft_memalloc(sizeof(t_bin_item *) * bin->size)))
		error_malloc(shell, bin, "t_bin_items");;
    return (bin);
}
