/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:04:15 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/03 19:14:40 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		sh_glob_cbraces_dots_expand(t_cbraces *cb)
{
	cb->before = ft_strsub(cb->str, 0, cb->start);
	cb->after = ft_strdups(cb->str + cb->stop + 1);
	(ft_isint(cb->left))
		? sh_glob_cbraces_rp_num(cb)
		: sh_glob_cbraces_rp_alpha(cb);
}

static char	sh_glob_cbraces_dots_particular(t_cbraces *cb, char *substr)
{
	char	*str;

	str = sh_glob_cbraces(substr);
	cb->before = ft_strsub(cb->str, 0, cb->start);
	cb->after = ft_strdups(cb->str + cb->stop + 1);
	return (-1);
}

char		sh_glob_cbraces_dots(t_cbraces *cb)
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
			(cb->left) ? cb->left[i] = '\0' : 0;
			cb->right = ft_strdups(substr + i + 2);
			if (sh_glob_cbraces_check(cb->left)
			|| sh_glob_cbraces_check(cb->right))
				return (sh_glob_cbraces_dots_particular(cb, substr));
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
