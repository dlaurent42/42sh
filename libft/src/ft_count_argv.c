/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/01 16:46:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 20:09:26 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_count_argv(void **array)
{
	size_t	count;

	count = 0;
	if (!array)
		return (0);
	while (array[count])
		count++;
	return (count);
}
