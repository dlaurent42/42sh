/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deltab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinoit <rpinoit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 21:33:46 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/28 21:35:20 by rpinoit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    ft_deltab(void *content)
{
    char **tmp;
    int i;

    i = 0;
    tmp = (char **)content;
    while (tmp[i])
        free(tmp[i++]);
    free(tmp);
}