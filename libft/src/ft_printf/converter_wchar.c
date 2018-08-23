/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_wchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 09:16:34 by dlaurent          #+#    #+#             */
/*   Updated: 2018/04/30 13:58:47 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_atoi_binary(char *s)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (s[i] >= '0' && s[i] <= '1')
	{
		result = result * 2 + (s[i] - 48);
		i++;
	}
	ft_strdel(&s);
	return (result);
}

static char	*get_mask(size_t i, size_t j, char *s1, char *s2)
{
	j--;
	i--;
	if (!s1 || !s2)
		return (NULL);
	while (j)
	{
		if (s2[j] == 'x' && (int)i > -1)
		{
			s2[j] = s1[i];
			i--;
		}
		else if (s2[j] == 'x')
			s2[j] = '0';
		j--;
	}
	return (s2);
}

static char	*forced_strsub(char const *s, unsigned int start, size_t len)
{
	char	*d;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(d = ft_strnew(sizeof(char) * len)))
		return (NULL);
	while (start--)
		j++;
	while (len--)
		d[i++] = s[j++];
	return (d);
}

static char	*get_binary(wchar_t c, char *src, t_arg *args)
{
	int		i;
	char	*dst;

	i = 0;
	dst = NULL;
	if (!src)
		return (ft_strdup(""));
	if ((unsigned int)c <= 0x7FF)
		i = 1;
	else if ((unsigned int)c <= 0xFFFF)
		i = 2;
	else if ((unsigned int)c <= 0x1FFFFF)
		i = 3;
	if (!(dst = ft_strnew(sizeof(char) * (i + 1))))
		return (NULL);
	args->len += i + 1;
	while (i)
	{
		dst[i] = ft_atoi_binary(forced_strsub(src, 8 * i, 8));
		i--;
	}
	dst[0] = ft_atoi_binary(forced_strsub(src, 0, 8));
	ft_strdel(&src);
	return (dst);
}

char		*convert_wchar(wchar_t c, t_arg *args)
{
	char	*s1;
	char	*s2;

	s1 = ulltoa_base("01", (unsigned int)c);
	s2 = NULL;
	if ((unsigned int)c <= 0x7F)
	{
		if (!(s2 = ft_strnew(sizeof(char))))
			return (NULL);
		s2[0] = (char)c;
		args->len += 1;
		ft_strdel(&s1);
		return (s2);
	}
	else if ((unsigned int)c <= 0x7FF)
		s2 = get_mask(ft_strlens(s1), ft_strlens(MASK1), s1, ft_strdups(MASK1));
	else if ((unsigned int)c <= 0xFFFF)
		s2 = get_mask(ft_strlens(s1), ft_strlens(MASK2), s1, ft_strdups(MASK2));
	else if ((unsigned int)c <= 0x1FFFFF)
		s2 = get_mask(ft_strlens(s1), ft_strlens(MASK3), s1, ft_strdups(MASK3));
	else
		s2 = NULL;
	ft_strdel(&s1);
	s1 = get_binary(c, s2, args);
	return (s1);
}
