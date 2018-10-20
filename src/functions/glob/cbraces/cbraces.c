/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbraces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 23:43:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/20 17:30:53 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_glob_cbraces_start_stop(t_cbraces *cb)
{
	int		i;
	int		more;

	i = 0;
	more = 0;
	ft_printf(". Entering start and stop [%s]\n", cb->str);
	while (cb->str[i] && !(cb->start > -1 && cb->stop > -1 && more == 0))
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
		// ft_printf("... start: %d, stop: %d; more: %d, char: %c, i: %d\n", cb->start, cb->stop, more, cb->str[i], i);
		i++;
	}
	ft_printf(". Exiting start and stop\n");
	if (cb->start > -1 && cb->stop > -1 && more == 0)
		return (TRUE);
	return (FALSE);
}

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

bool		sh_glob_cbraces_check(char *str)
{
	int			i;
	bool		res;
	t_cbraces	*cb;

	i = 0;
	res = FALSE;
	ft_printf("received str : [%s]\n", str);
	if (glob_strcountif(str, '{') == 0 || glob_strcountif(str, '}') == 0
	|| !(cb = (t_cbraces *)ft_memalloc(sizeof(t_cbraces))))
	{
		ft_printf("check res = FALSE\n");
		return (FALSE);
	}
	cb->start = -1;
	cb->stop = -1;
	if ((!(cb->str = ft_strdups(str)) || sh_glob_cbraces_start_stop(cb)))
	{
		if (sh_glob_cbraces_list(cb))
			res = TRUE;
		else if (sh_glob_cbraces_dots(cb))
			res = TRUE;
	}
	ft_printf("check res = %d\n", res);
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

char		*sh_glob_cbraces(char *str)
{
	t_cbraces	*cb;

	ft_printf("New glob braces: [%s]\n", str);
	if (glob_strcountif(str, '{') == 0 || glob_strcountif(str, '}') == 0
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
