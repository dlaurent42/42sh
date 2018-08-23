/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:58:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/08/02 11:20:50 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int			i;
	int			j;
	const char	*occ;

	i = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	else
		while (haystack && haystack[i])
		{
			j = 0;
			occ = &haystack[i];
			while (haystack[i + j] == needle[j])
			{
				if (needle[j + 1] == '\0')
					return ((char *)occ);
				j++;
			}
			i++;
		}
	return (NULL);
}
