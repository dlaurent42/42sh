/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 13:07:53 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/20 17:32:05 by dlaurent         ###   ########.fr       */
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
	ft_printf(". Entering expansion with str: [%s], before: [%s] and after: [%s]\n", cb->str, cb->before, cb->after);
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
		ft_printf("... before new instance [%s]\n-------------------------------------------\n", cb->str);
		cb->str = sh_glob_cbraces(cb->str);
		i++;
	}
	cb->str = ft_strjoinf(ft_strsub(cb->before, 0, pos), cb->str, 3);
	ft_printf(". Exiting expansion with str: [%s]\n", cb->str);
}

static char	*sh_glob_cbraces_list_particular_case(char *str)
{
	int		i;

	i = -1;
	if (!str)
		return (str);
	ft_printf("Initial str: [%s]\n", str);
	while (str[++i])
		if (i == 0)
			str = sh_glob_inject(str, "\\{", i);
		else if (i && str[i] == ' ' && str[i - 1] != ' ')
		{
			str = sh_glob_inject(str, "\\}", i);
			i += 2;
		}
		else if (i && str[i] != ' ' && str[i - 1] == ' ')
		{
			str = sh_glob_inject(str, "\\{", i);
			i += 2;
		}
		else if (str[i] != ' ' && !str[i + 1])
			return (sh_glob_inject(str, "\\}", i + 1));
	return (str);
}

static int	sh_glob_cbraces_list_rearrange(t_cbraces *cb, int i)
{
	int		count;
	char	*str;

	str = NULL;
	cb->split[i] = sh_glob_cbraces_list_particular_case(sh_glob_cbraces(cb->split[i]));
	count = glob_strcountif(cb->split[i], ' ');
	ft_printf("After str: [%s]\n", cb->split[i]);
	i = 0;
	while (cb->split[i])
	{
		(str) ? str = ft_strjoinf(str, " ", 1) : 0;
		str = ft_strjoinf(str, cb->split[i], 3);
		i++;
	}
	ft_printf("After join : [%s]\n", str);
	free(cb->split);
	cb->split = ft_strsplit(str, ' ');
	ft_strdel(&str);
	ft_printf("count returned %d\n", count);
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
		ft_printf("... checking: [%s]\n", cb->split[i]);
		if (sh_glob_cbraces_check(cb->split[i]))
		{
			ft_printf(".................... was: [%s]\n", cb->split[i]);
			/*
			** Deplacer l'assignation before/after avant le split
			** Créer une function qui split le retour de sh_glob_cbraces
			** en fonction des espaces.
			** pour chaque element de ce split, faire le join suivant:
			**	before + \{ + split[i] + \} + after
			** reconcatener l'ensemble
			** permet de gérer "abc{{A,b}..2}def"
			*/
			i += sh_glob_cbraces_list_rearrange(cb, i);
			//cb->split[i] = sh_glob_cbraces(cb->split[i]);
			ft_printf(".................... after checking now: [%s]\n", cb->split[i]);
		}
		else
			while (cb->split[i][j])
			{
				if (glob_need_esc(cb->split[i][j]) && !glob_is_esc(cb->split[i], j))
				{
					ft_printf("... list char need esc but not esc\n");
					return (FALSE);
				}
				else if (glob_is_esc(cb->split[i], j)
				&& !glob_need_esc(cb->split[i][j]))
					sh_glob_repatriate(cb->split[i], j, 1);
				j++;
			}
		ft_printf("..... now: [%s]\n", cb->split[i]);
		i++;
	}
	ft_printf(". Exiting is_list\n");
	return (TRUE);
}

bool		sh_glob_cbraces_list(t_cbraces *cb)
{
	int		i;
	char	*substr;

	i = 0;
	if (!(substr = ft_strsub(cb->str, cb->start + 1, cb->stop - cb->start - 1)))
		return (FALSE);
	ft_printf(". Entering is_list with substr: [%s]\n", substr);
	if (glob_strcountif(substr, ',') == 0 || glob_strcountif(substr, ' '))
	{
		ft_strdel(&substr);
		ft_printf(". Exiting is_list (not a list 1)\n");
		return (FALSE);
	}
	cb->split = glob_strsplit(substr, ',');
	ft_strdel(&substr);
	if (!cb->split)
	{
		ft_printf(". Exiting is_list (not a list 2)\n");
		return (FALSE);
	}
	return (sh_glob_cbraces_list_check(cb));
}
