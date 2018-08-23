/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:58:23 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/03 14:58:24 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		arr_length;
	int		n;
	char	tmp;

	tmp = 0;
	arr_length = 0;
	n = 0;
	while (str[arr_length] != '\0')
		arr_length++;
	while (n < arr_length / 2 + arr_length % 2)
	{
		tmp = str[n];
		str[n] = str[arr_length - n];
		str[arr_length - n] = tmp;
		n++;
	}
	return (str);
}
