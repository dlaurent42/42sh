/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 23:34:59 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/11 23:35:02 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memsets(void *b, int c, size_t len)
{
	if (!b)
		return (NULL);
	while (len--)
		((unsigned char *)b)[len] = (unsigned char)c;
	return (b);
}
