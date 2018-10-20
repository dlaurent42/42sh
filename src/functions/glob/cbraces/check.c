/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 18:08:55 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/20 18:57:08 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

bool		sh_glob_cbraces_check(char *str)
{
	int			i;
	bool		res;
	t_cbraces	*cb;

	i = 0;
	res = FALSE;
	if (glob_strcountif(str, '{') == 0 || glob_strcountif(str, '}') == 0
	|| !(cb = (t_cbraces *)ft_memalloc(sizeof(t_cbraces))))
		return (0);
	cb->start = -1;
	cb->stop = -1;
	if ((!(cb->str = ft_strdups(str)) || sh_glob_cbraces_start_stop(cb)))
	{
		if (sh_glob_cbraces_dots(cb))
			res = TRUE;
		else if (sh_glob_cbraces_list(cb))
			res = TRUE;
	}
	ft_strdel(&cb->str);
	ft_strdel(&cb->left);
	ft_strdel(&cb->right);
	ft_strdel(&cb->before);
	ft_strdel(&cb->after);
	if (cb->split)
		while (cb->split[i])
		{
			ft_strdel(&cb->split[i]);
			i++;
		}
	(cb->split) ? free(cb->split) : 0;
	(cb) ? free(cb) : 0;
	return (res);
}
