/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 19:06:33 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/06 20:45:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*ft_joinchar(char *s, char c, bool to_free)
{
	char	*new;
	size_t	len;

	len = ft_strlens(s);
	if (!s)
	{
		if (!(s = ft_strnew(2)))
			return (NULL);
		s[0] = c;
		return (s);
	}
	if (!(new = ft_strnew(len + 1)))
		return (NULL);
	new = ft_strcpy(new, s);
	new[len] = c;
	(to_free) ? ft_strdel(&s) : 0;
	return (new);
}

static char	*sh_glob_cbraces_rp_alpha_join(t_cbraces **cb, char val)
{
	if (val > 90 && val < 97)
		return (ft_strjoinf((*cb)->str, ft_joinchar("\\", val, false), 3));
	return (ft_joinchar((*cb)->str, val, true));
}

void		sh_glob_cbraces_rp_alpha(t_cbraces *cb)
{
	int		i;
	int		pos;
	char	min;
	char	max;

	i = -1;
	pos = 0;
	while (cb->before && cb->before[++i])
		if (i && cb->before[i] != ' ' && cb->before[i - 1] == ' ')
			pos = i;
	min = (cb->left[0] < cb->right[0]) ? cb->left[0] : cb->right[0];
	max = (cb->left[0] < cb->right[0]) ? cb->right[0] : cb->left[0];
	ft_strdel(&cb->str);
	while (min <= max)
	{
		(cb->str) ? cb->str = ft_strjoinf(cb->str, " ", 1) : 0;
		cb->str = ft_strjoinf(cb->str, cb->before + pos, 1);
		cb->str = (cb->left[0] < cb->right[0])
			? sh_glob_cbraces_rp_alpha_join(&cb, min)
			: sh_glob_cbraces_rp_alpha_join(&cb, max);
		cb->str = ft_strjoinf(cb->str, cb->after, 1);
		cb->str = sh_glob_cbraces(cb->str);
		(cb->left[0] < cb->right[0]) ? min++ : max--;
	}
	cb->str = ft_strjoinf(ft_strsub(cb->before, 0, pos), cb->str, 3);
}

void		sh_glob_cbraces_rp_num(t_cbraces *cb)
{
	int		i;
	int		pos;
	int		min;
	int		max;
	char	direction;

	i = -1;
	pos = 0;
	while (cb->before && cb->before[++i])
		if (i && cb->before[i] != ' ' && cb->before[i - 1] == ' ')
			pos = i;
	direction = (ft_atoi(cb->left) > ft_atoi(cb->right)) ? -1 : 1;
	min = (direction == 1) ? ft_atoi(cb->left) : ft_atoi(cb->right);
	max = (direction == 1) ? ft_atoi(cb->right) : ft_atoi(cb->left);
	ft_strdel(&cb->str);
	while (min <= max)
	{
		(cb->str) ? cb->str = ft_strjoinf(cb->str, " ", 1) : 0;
		cb->str = ft_strjoinf(cb->str, cb->before + pos, 1);
		cb->str = (direction == 1) ? ft_strjoinf(cb->str, ft_itoa(min++), 3)
			: ft_strjoinf(cb->str, ft_itoa(max--), 3);
		cb->str = ft_strjoinf(cb->str, cb->after, 1);
		cb->str = sh_glob_cbraces(cb->str);
	}
	cb->str = ft_strjoinf(ft_strsub(cb->before, 0, pos), cb->str, 3);
}
