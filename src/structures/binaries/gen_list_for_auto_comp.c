/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_list_for_auto_comp.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 18:55:08 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 22:19:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void				bin_gen_list_for_auto_comp(t_shell *sh, t_bin *bin, char *s)
{
	t_bin_auto		*new;

	if (ft_strcmps(s, ".") && ft_strcmps(s, ".."))
	{
		if (!(new = (t_bin_auto *)ft_memalloc(sizeof(t_bin_auto))))
			error_malloc_bin(sh, bin, "t_bin_auto structure");
		if (!(new->name = ft_strdup(s)))
		{
			free(new);
			error_malloc_bin(sh, bin, "t_bin_auto name string");
		}
		new->next = bin->bin_auto;
		bin->bin_auto = new;
	}
}
