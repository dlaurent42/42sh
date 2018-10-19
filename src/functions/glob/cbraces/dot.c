/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:04:15 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/19 14:23:37 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_glob_cbraces_rp_alpha_join(t_cbraces *cb, char min, int pos)
{
	if (cb->str)
		cb->str = ft_strjoinf(cb->str, " ", 1);
	cb->str = ft_strjoinf(cb->str, cb->before + pos, 1);
	cb->str = (min > 90 && min < 97)
		? ft_strjoinf(cb->str, ft_strjoins("\\", &min), 3)
		: ft_strjoinf(cb->str, &(min), 1);
	cb->str = ft_strjoinf(cb->str, cb->after, 1);
	cb->str = sh_glob_cbraces(cb->str);
}

static bool	sh_glob_cbraces_rp_alpha(t_cbraces *cb)
{
	int		i;
	int		pos;
	char	min;
	char	max;

	i = -1;
	pos = 0;
	if (cb->before)
		while (cb->before[++i])
			if (i && cb->before[i] != ' ' && cb->before[i - 1] == ' ')
				pos = i;
	min = (cb->left[0] > cb->right[0]) ? cb->right[0] : cb->left[0];
	max = (cb->left[0] < cb->right[0]) ? cb->right[0] : cb->left[0];
	ft_strdel(&cb->str);
	while (min <= max)
	{
		sh_glob_cbraces_rp_alpha_join(cb, min, pos);
		min++;
	}
	cb->str = ft_strjoinf(ft_strsub(cb->before, 0, pos), cb->str, 3);
	return (TRUE);
}

static bool	sh_glob_cbraces_rp_num(t_cbraces *cb)
{
	int		i;
	int		pos;
	int		min;
	int		max;

	i = -1;
	pos = 0;
	while (cb->before && cb->before[++i])
		if (i && cb->before[i] != ' ' && cb->before[i - 1] == ' ')
			pos = i;
	min = (ft_atoi(cb->left) > ft_atoi(cb->right))
		? ft_atoi(cb->right) : ft_atoi(cb->left);
	max = (ft_atoi(cb->left) < ft_atoi(cb->right))
		? ft_atoi(cb->right) : ft_atoi(cb->left);
	ft_strdel(&cb->str);
	while (min <= max)
	{
		(cb->str) ? cb->str = ft_strjoinf(cb->str, " ", 1) : 0;
		cb->str = ft_strjoinf(cb->str, cb->before + pos, 1);
		cb->str = ft_strjoinf(cb->str, ft_itoa(min++), 3);
		cb->str = ft_strjoinf(cb->str, cb->after, 1);
		cb->str = sh_glob_cbraces(cb->str);
	}
	cb->str = ft_strjoinf(ft_strsub(cb->before, 0, pos), cb->str, 3);
	return (TRUE);
}

void		sh_glob_cbraces_dots_expand(t_cbraces *cb)
{
	cb->before = ft_strsub(cb->str, 0, cb->start);
	cb->after = ft_strdups(cb->str + cb->stop + 1);
	(ft_isint(cb->left)
		? sh_glob_cbraces_rp_num(cb)
		: sh_glob_cbraces_rp_alpha(cb));
}

bool		sh_glob_cbraces_dots(t_cbraces *cb)
{
	int		i;
	char	*substr;

	i = 0;
	if (!(substr = ft_strsub(cb->str, cb->start + 1, cb->stop - cb->start - 1)))
		return (FALSE);
	cb->left = ft_strdups(substr);
	while (substr[i])
	{
		if (substr[i] == '.' && substr[i + 1] == '.' && substr[i + 2])
		{
			if (cb->left)
				cb->left[i] = '\0';
			cb->right = ft_strdups(substr + i + 2);
			break ;
		}
		i++;
	}
	ft_strdel(&substr);
	return (cb->left && cb->right
	&& ((ft_isint(cb->left) && ft_isint(cb->right))
	|| (ft_isalpha(cb->left[0]) && !cb->left[1]
	&& ft_isalpha(cb->right[0]) && !cb->right[1])));
}
