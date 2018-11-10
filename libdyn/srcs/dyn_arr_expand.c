/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_arr_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:41:23 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:47:57 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdyn.h"

void	dyn_arr_expand(t_array *arr, size_t mem_len)
{
	void	*new;

	arr->capacity <<= 1;
	if ((new = malloc(arr->capacity)) != NULL)
	{
		dyn_arr_copy(&new, arr->content, arr->size * mem_len);
		free(arr->content);
		arr->content = new;
	}
}
