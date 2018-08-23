/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmatch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:59:11 by dlaurent          #+#    #+#             */
/*   Updated: 2018/06/28 21:48:20 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		check_combinaisons(int i, int j, char *s1, char *s2)
{
	if (s1[i] != '\0')
	{
		if (s2[j] == '\0')
			return (0);
		else if (s2[j] == '*')
			return (check_combinaisons(i, j + 1, s1, s2)
			+ check_combinaisons(i + 1, j, s1, s2));
		else if (s1[i] == s2[j])
			return (check_combinaisons(i + 1, j + 1, s1, s2));
		else
			return (0);
	}
	else if (s1[i] == '\0')
	{
		if (s2[j] == '\0')
			return (1);
		else if (s2[j] == '*')
			return (check_combinaisons(i, j + 1, s1, s2));
		else
			return (0);
	}
	return (0);
}

int				nmatch(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (0);
	return (check_combinaisons(0, 0, s1, s2));
}
