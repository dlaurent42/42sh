/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strleft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:02:10 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/16 15:50:50 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strleft(char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] && len)
	{
		if (i >= len)
			src[i] = '\0';
		i++;
	}
	return ((char *)src);
}
