/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 22:38:07 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/11 17:27:06 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strcasecmp(const char *s1, const char *s2)
{
	return (ft_strncasecmp(s1, s2, ft_strlen(s1) + 1));
}
