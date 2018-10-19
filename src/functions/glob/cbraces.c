/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbraces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 23:43:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/19 11:48:34 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		(cb->str) ? cb->str = ft_strjoinf(cb->str, " ", 1) : 0;
		cb->str = ft_strjoinf(cb->str, cb->before + pos, 1);
		cb->str = ft_strjoinf(cb->str, &(min), 1);
		cb->str = ft_strjoinf(cb->str, cb->after, 1);
		cb->str = sh_glob_cbraces(cb->str);
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

static bool	sh_glob_cbraces_left_right(t_cbraces *cb)
{
	int		i;
	char	*substr;

	i = 0;
	substr = ft_strsub(cb->str, cb->start + 1, cb->stop - cb->start - 1);
	if (!substr)
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

static bool	sh_glob_cbraces_start_stop(t_cbraces *cb)
{
	int		i;

	i = 0;
	while (cb->str[i] && !(cb->start != -1 && cb->stop != -1))
	{
		if ((cb->start != -1 || cb->stop != -1) && cb->str[i] == '{')
			return (FALSE);
		else if (cb->start == -1 && cb->str[i] == '}')
			return (FALSE);
		else if (cb->str[i] == '{')
			cb->start = i;
		else if (cb->str[i] == '}')
			cb->stop = i;
		i++;
	}
	if (cb->start != -1 && cb->stop != -1)
		return (TRUE);
	return (FALSE);
}

char		*sh_glob_cbraces(char *str)
{
	char		*tmp;
	t_cbraces	*cb;

	if (!str || !(cb = (t_cbraces *)ft_memalloc(sizeof(t_cbraces))))
		return (str);
	cb->start = -1;
	cb->stop = -1;
	if ((!(cb->str = ft_strdups(str)) || sh_glob_cbraces_start_stop(cb)))
		if (sh_glob_cbraces_left_right(cb))
		{
			cb->before = ft_strsub(cb->str, 0, cb->start);
			cb->after = ft_strdups(cb->str + cb->stop + 1);
			(ft_isint(cb->left)
				? sh_glob_cbraces_rp_num(cb)
				: sh_glob_cbraces_rp_alpha(cb));
		}
	tmp = ft_strdups(cb->str);
	ft_strdel(&str);
	ft_strdel(&cb->str);
	ft_strdel(&cb->left);
	ft_strdel(&cb->right);
	ft_strdel(&cb->before);
	ft_strdel(&cb->after);
	(cb) ? free(cb) : 0;
	return (tmp);
}
