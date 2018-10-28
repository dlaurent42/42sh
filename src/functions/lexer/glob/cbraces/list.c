/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:07:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:58:38 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_glob_cbraces_expand(t_cbraces *cb)
{
	int		i;
	int		pos;

	i = -1;
	pos = 0;
	(!cb->before) ? cb->before = ft_strsub(cb->str, 0, cb->start) : 0;
	(!cb->after) ? cb->after = ft_strdups(cb->str + cb->stop + 1) : 0;
	while (cb->before && cb->before[++i])
		if (i && cb->before[i] != ' ' && cb->before[i - 1] == ' ')
			pos = i;
	i = 0;
	ft_strdel(&cb->str);
	while (cb->split[i])
	{
		(cb->str) ? cb->str = ft_strjoinf(cb->str, " ", 1) : 0;
		cb->str = ft_strjoinf(cb->str, cb->before + pos, 1);
		cb->str = ft_strjoinf(cb->str, cb->split[i], 1);
		cb->str = ft_strjoinf(cb->str, cb->after, 1);
		cb->str = sh_glob_cbraces(cb->str);
		i++;
	}
	cb->str = ft_strjoinf(ft_strsub(cb->before, 0, pos), cb->str, 3);
}

static int	sh_glob_cbraces_list_rearrange(t_cbraces *cb, int i)
{
	int		count;
	char	*str;

	str = NULL;
	cb->split[i] = sh_glob_cbraces(cb->split[i]);
	count = lexer_strcountif(cb->split[i], ' ');
	i = 0;
	while (cb->split[i])
	{
		(str) ? str = ft_strjoinf(str, " ", 1) : 0;
		str = ft_strjoinf(str, cb->split[i], 3);
		i++;
	}
	free(cb->split);
	cb->split = ft_strsplit(str, ' ');
	ft_strdel(&str);
	return (count);
}

static bool	sh_glob_cbraces_list_check(t_cbraces *cb)
{
	int		i;
	int		j;

	i = 0;
	while (cb->split[i])
	{
		j = 0;
		if (sh_glob_cbraces_check(cb->split[i]))
			i += sh_glob_cbraces_list_rearrange(cb, i);
		else
			while (cb->split[i][j])
			{
				if (lexer_need_esc(cb->split[i][j])
				&& !lexer_is_esc(cb->split[i], j))
					return (FALSE);
				else if (lexer_is_esc(cb->split[i], j)
				&& !lexer_need_esc(cb->split[i][j]))
					lexer_repatriate(cb->split[i], j, 1);
				j++;
			}
		i++;
	}
	return (TRUE);
}

bool		sh_glob_cbraces_list(t_cbraces *cb)
{
	int		i;
	char	*substr;

	i = 0;
	if (!(substr = ft_strsub(cb->str, cb->start + 1, cb->stop - cb->start - 1)))
		return (FALSE);
	if (lexer_strcountif(substr, ',') == 0 || lexer_strcountif(substr, ' '))
	{
		ft_strdel(&substr);
		return (FALSE);
	}
	cb->split = cbraces_strsplit(substr, ',');
	ft_strdel(&substr);
	if (!cb->split)
		return (FALSE);
	return (sh_glob_cbraces_list_check(cb));
}
