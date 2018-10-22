/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_arr_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:40:32 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/04 17:40:35 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdyn.h"

void	dyn_arr_init(t_array *arr, void *content, size_t capacity, size_t size)
{
	arr->content = content;
	arr->capacity = capacity;
	arr->size = size;
}
