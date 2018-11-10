/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deltab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akarasso <akarasso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 21:33:46 by akarasso          #+#    #+#             */
/*   Updated: 2018/11/10 20:48:26 by azaliaus         ###   ########.fr       */
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
