/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbraces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 23:43:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:55:17 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_glob_cbraces_del(t_cbraces *cb, char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdups(cb->str);
	ft_strdel(&str);
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
	return (tmp);
}

char		*sh_glob_cbraces(char *str)
{
	t_cbraces	*cb;

	if (lexer_strcountif(str, '{') == 0 || lexer_strcountif(str, '}') == 0
	|| !(cb = (t_cbraces *)ft_memalloc(sizeof(t_cbraces))))
		return (str);
	cb->start = -1;
	cb->stop = -1;
	if ((!(cb->str = ft_strdups(str)) || sh_glob_cbraces_start_stop(cb)))
	{
		if (sh_glob_cbraces_list(cb) > 0)
			sh_glob_cbraces_expand(cb);
		else if (sh_glob_cbraces_dots(cb) > 0)
			sh_glob_cbraces_dots_expand(cb);
	}
	return (sh_glob_cbraces_del(cb, str));
}
