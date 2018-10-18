/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbraces.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 23:43:56 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/19 00:07:20 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_glob_cbraces_start_stop(t_cbraces *cbraces)
{
	int		i;

	i = -1;
	while (cbraces->str[++i] && !(start != -1 && stop != -1))
		if (((start != -1 || stop != -1) && cbraces->str[i] == '{')
		|| (start == -1 && cbraces->str[i] == '}'))
			return (FALSE);
		else if (cbraces->str[i] == '{')
			start = i;
		else if (cbraces->str[i] == '}')
			stop = i;
	if (start != -1 && stop != -1
	&& sh_glob_brackets_left_right(cbraces, start + 1, stop - 1))
	{
		glob->before = ft_strdups(cbraces->str);
		glob->before[start - 1] = '\0';
		glob->after = ft_strdups(cbraces->str + stop + 1);
		return ((ft_isint(glob->left))
		? sh_glob_brackets_rp_num(glob) : sh_glob_brackets_rp_alpha(cbraces));
	}
	return (FALSE);
}

char		*sh_glob_cbraces(char *str)
{
	char		*tmp;
	t_cbraces	*cbraces;

	if (!str)
		return (str);
	if (!(cbraces = (t_cbraces *)ft_memalloc(sizeof(cbraces))))
		return (str);
	cbraces->start = -1;
	cbraces->stop = -1;
	cbraces->str = ft_strdups(str);
	if (sh_glob_cbraces_start_stop(cbraces))
		if ()
	call_program(cbraces);
	tmp = ft_strdups(cbraces->str);
	ft_strdel(&str);
	ft_strdel(&cbraces->str);
	ft_strdel(&cbraces->left);
	ft_strdel(&cbraces->right);
	ft_strdel(&cbraces->before);
	ft_strdel(&cbraces->after);
	(cbraces) ? free(cbraces) : 0;
	return (tmp);
}
