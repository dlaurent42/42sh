/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstartsby.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 19:57:05 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 19:58:41 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_strstartsby(char *origin, char *seek)
{
	int	i;

	i = 0;
	if (!origin || !seek)
		return (FALSE);
	while (origin[i] && seek[i] && origin[i] == seek[i])
		i++;
	if (seek[i])
		return (FALSE);
	return (TRUE);
}
