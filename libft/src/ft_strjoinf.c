/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 19:01:18 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/12 19:22:01 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoinf_opt(char *s1, char *s2, int opt)
{
	char	*d;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	d = NULL;
	if (!(d = ft_strnew((ft_strlen(s1) + ft_strlen(s2)))))
		return (NULL);
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		d[i + j] = s2[j];
		j++;
	}
	if (opt == 1 || opt == 3)
		ft_strdel(&s1);
	if (opt == 2 || opt == 3)
		ft_strdel(&s2);
	return (d);
}

static char	*dup_and_del(char *s)
{
	char	*d;

	d = ft_strdup(s);
	if (s)
		ft_strdel(&s);
	return (d);
}

char		*ft_strjoinf(char *s1, char *s2, int opt)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
	{
		if (opt == 2 || opt == 3)
			return (dup_and_del(s2));
		else
			return (ft_strdup(s2));
	}
	if (!s2 && s1)
	{
		if (opt == 1 || opt == 3)
			return (dup_and_del(s1));
		else
			return (ft_strdup(s1));
	}
	return (ft_strjoinf_opt(s1, s2, opt));
}
