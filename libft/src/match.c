/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:59:07 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/04 12:41:12 by dlaurent         ###   ########.fr       */
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
			if (check_combinaisons(i, j + 1, s1, s2) == 0)
				return (check_combinaisons(i + 1, j, s1, s2));
			else
				return (check_combinaisons(i, j + 1, s1, s2));
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

int				match(char *s1, char *s2)
{
	return (check_combinaisons(0, 0, s1, s2));
}
