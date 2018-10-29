/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deltab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 21:33:46 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/29 17:21:46 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_deltab(void *content)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = (char **)content;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}
