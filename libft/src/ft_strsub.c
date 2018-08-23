/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:58:40 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/11 15:15:06 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;
	size_t	j;

	j = 0;
	if (!s)
		return (NULL);
	if (!(d = ft_strnew(sizeof(char) * len)))
		return (NULL);
	while (start-- && s[j])
		j++;
	i = 0;
	while (len-- && s[j])
		d[i++] = s[j++];
	return (d);
}
