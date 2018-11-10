/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_arr_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:40:32 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:47:58 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdyn.h"

void	dyn_arr_init(t_array *arr, void *content, size_t capacity, size_t size)
{
	arr->content = content;
	arr->capacity = capacity;
	arr->size = size;
}
