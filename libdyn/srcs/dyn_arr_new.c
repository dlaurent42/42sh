/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_arr_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:40:59 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:48:00 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libdyn.h"

void	*dyn_arr_new(void *src, size_t len)
{
	void	*new;

	if ((new = malloc(len)) != NULL)
		dyn_arr_copy(&new, src, len);
	return (new);
}
