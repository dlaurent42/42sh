/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 19:01:58 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/08 19:02:04 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlens(const char *s)
{
	size_t len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
		len++;
	return (len);
}
