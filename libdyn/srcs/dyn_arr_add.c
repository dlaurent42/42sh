/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_arr_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:39:27 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:47:54 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdyn.h"

void		dyn_arr_add(t_array *arr, void *src, size_t src_len, size_t mem_len)
{
	void	*new;
	void	*arr_end;
	size_t	total_arr;
	size_t	total_src;

	total_arr = arr->size * mem_len;
	total_src = src_len * mem_len;
	if (arr->content == NULL)
	{
		new = dyn_arr_new(src, total_src);
		dyn_arr_init(arr, new, total_src, src_len);
	}
	else
	{
		if (arr->capacity < total_arr + total_src)
		{
			dyn_arr_expand(arr, mem_len);
		}
		arr_end = arr->content + total_arr;
		dyn_arr_copy(&arr_end, src, total_src);
		arr->size += src_len;
	}
}
