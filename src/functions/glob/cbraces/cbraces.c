/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbraces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 23:43:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/19 15:09:11 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_glob_cbraces_start_stop(t_cbraces *cb)
{
	int		i;
	int		more;

	i = 0;
	more = 0;
	while (cb->str[i] && !(cb->start > -1 && cb->stop > -1 && more))
	{
		if (cb->start > -1 && cb->str[i] == '{' && !glob_is_esc(cb->str, i))
			more++;
		else if (cb->stop > -1 && cb->str[i] == '{' && !glob_is_esc(cb->str, i))
			return (FALSE);
		else if (cb->start == -1 && cb->str[i] == '}'
		&& !glob_is_esc(cb->str, i))
			return (FALSE);
		else if (cb->str[i] == '{' && !glob_is_esc(cb->str, i))
			cb->start = i;
		else if (cb->str[i] == '}' && more && !glob_is_esc(cb->str, i))
			more--;
		else if (cb->str[i] == '}' && !glob_is_esc(cb->str, i))
			cb->stop = i;
		i++;
	}
	if (cb->start > -1 && cb->stop > -1 && more == 0)
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
		if (sh_glob_cbraces_list(cb))
			sh_glob_cbraces_expand(cb);
		else if (sh_glob_cbraces_dots(cb))
			sh_glob_cbraces_dots_expand(cb);
	tmp = ft_strdups(cb->str);
	ft_strdel(&str);
	ft_strdel(&cb->str);
	ft_strdel(&cb->left);
	ft_strdel(&cb->right);
	ft_strdel(&cb->before);
	ft_strdel(&cb->after);
	// Delete split
	(cb) ? free(cb) : 0;
	return (tmp);
}
