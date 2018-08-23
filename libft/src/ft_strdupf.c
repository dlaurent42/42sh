/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdupf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 19:00:21 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/12 00:05:51 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupf(char *s1)
{
	char	*dst;

	if (!s1)
		return (NULL);
	if (!(dst = ft_strnew(sizeof(char) * ft_strlen(s1))))
		return (NULL);
	dst = ft_strcpy(dst, s1);
	ft_strdel(&s1);
	return (dst);
}
