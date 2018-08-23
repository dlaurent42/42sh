/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcountif.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:44:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/05/10 17:45:48 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcountif(char *s, char c)
{
	int	i;
	int	occ;

	i = 0;
	occ = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			occ++;
		i++;
	}
	return (occ);
}
