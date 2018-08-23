/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strleft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:02:10 by dlaurent          #+#    #+#             */
/*   Updated: 2018/06/11 12:13:13 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strleft(const char *src, size_t len)
{
	if (!src)
		return (NULL);
	while (*src && len)
	{
		src++;
		len--;
	}
	return ((char *)src);
}
