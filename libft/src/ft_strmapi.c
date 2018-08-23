/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:57:50 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/03 14:57:51 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	size_t			i;
	unsigned int	index;

	i = 0;
	if (!s || !f)
		return (NULL);
	index = 0;
	if (!(str = ft_strnew(sizeof(char) * (ft_strlen(s)))))
		return (NULL);
	while (s[i])
	{
		str[i] = f(index++, s[i]);
		i++;
	}
	return (str);
}
