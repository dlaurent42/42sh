/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:07:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/19 15:03:39 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_glob_cbraces_list_check(t_cbraces *cb)
{
	int		i;
	int		j;

	i = 0;
	while (cb->split[i])
	{
		j = 0;
		while (cb->split[i][j])
		{
			if (glob_need_esc(cb->split[i][j]) && !glob_is_esc(cb->split[i], j))
				return (FALSE);
			else if (glob_is_esc(cb->split[i], j)
			&& !glob_need_esc(cb->split[i][j]))
				sh_glob_repatriate(cb->split[i], j, 1);
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
	char	**split;

	i = 0;
	if (!(substr = ft_strsub(cb->str, cb->start + 1, cb->stop - cb->start - 1)))
		return (FALSE);
	if (glob_strcountif(substr, ',') == 0 || glob_strcountif(substr, ' '))
	{
		ft_strdel(&substr);
		return (FALSE);
	}
	cb->split = glob_strsplit(substr, ',');
	ft_strdel(&substr);
	if (!cb->split)
		return (FALSE);
	return (sh_glob_cbraces_list_check(cb));
}
