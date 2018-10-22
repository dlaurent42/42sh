/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libdyn.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/27 19:12:30 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/04 17:39:04 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBDYN_H
# define LIBDYN_H

# include <stdlib.h>
# include <string.h>

typedef struct	s_array
{
	void		*content;
	size_t		capacity;
	size_t		size;
}				t_array;

void			*dyn_arr_new(void *src, size_t len);
void			dyn_arr_add(t_array *arr, void *src, size_t src_len, \
					size_t mem_len);
void			dyn_arr_copy(void **arr, void *src, size_t len);
void			dyn_arr_init(t_array *arr, void *content, size_t capacity, \
					size_t size);
void			dyn_arr_expand(t_array *arr, size_t mem_len);

#endif
