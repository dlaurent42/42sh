/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbraces_working.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 20:19:11 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/18 23:49:13 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_glob_brackets_rp_alpha(t_glob *glob)
{
	char		min;
	char		max;

	min = (glob->left[0] > glob->right[0])
		? glob->right[0] : glob->left[0];
	max = (glob->left[0] < glob->right[0])
		? glob->right[0] : glob->left[0];
	ft_strdel(&glob->new);
	while (min <= max)
	{
		if (glob->new)
			glob->new = ft_strjoinf(glob->new, " ", 1);
		glob->new = ft_strjoinf(glob->new, glob->before, 1);
		glob->new = ft_strjoinf(glob->new, &min, 3);
		glob->new = ft_strjoinf(glob->new, glob->after, 1);
		min++;
	}
	ft_printf("Returning [%s]\n", glob->new);
	return (TRUE);
}

static bool	sh_glob_brackets_rp_num(t_glob *glob)
{
	int		i;
	int		pos;
	int		min;
	int		max;

	i = -1;
	pos = 0;
	if (glob->before)
		while (glob->before[++i])
			if (i && glob->before[i] != ' ' && glob->before[i - 1] == ' ')
				pos = i;
	min = (ft_atoi(glob->left) > ft_atoi(glob->right))
		? ft_atoi(glob->right) : ft_atoi(glob->left);
	max = (ft_atoi(glob->left) < ft_atoi(glob->right))
		? ft_atoi(glob->right) : ft_atoi(glob->left);
	ft_strdel(&glob->new);
	while (min <= max)
	{
		if (glob->new)
			glob->new = ft_strjoinf(glob->new, " ", 1);
		glob->new = ft_strjoinf(glob->new, glob->before + pos, 1);
		glob->new = ft_strjoinf(glob->new, ft_itoa(min), 3);
		glob->new = ft_strjoinf(glob->new, glob->after, 1);
		ft_printf("... At this stage [%s]\n", glob->new);
		glob->new = sh_glob(glob->new);
		min++;
	}
	glob->new = ft_strjoins(ft_strsub(glob->before, 0, pos), glob->new);
	ft_printf("... Returning [%s]\n", glob->new);
	return (TRUE);
}

static bool	sh_glob_brackets_left_right(t_glob *glob, int start, int stop)
{
	int		i;
	char	*substr;

	i = -1;
	ft_strdel(&glob->left);
	ft_strdel(&glob->right);
	substr = ft_strsub(glob->new, start, stop - start + 1);
	glob->left = ft_strdups(substr);
	while (substr && substr[++i])
		if (substr && substr[i] == '.' && substr[i + 1] == '.' && substr[i + 2])
		{
			(glob->left) ? glob->left[i] = '\0' : 0;
			glob->right = ft_strdups(substr + i + 2);
			break ;
		}
	ft_strdel(&substr);
	return ((glob->left && ft_isint(glob->left)
	&& glob->right && ft_isint(glob->right))
	|| (glob->left && ft_isalpha(glob->left[0]) && !glob->left[1]
	&& glob->right && ft_isalpha(glob->right[0]) && !glob->right[1]));
}

bool		sh_glob_brackets(t_glob *glob)
{
	int		i;
	int		start;
	int		stop;

	i = -1;
	start = -1;
	stop = -1;
	while (glob->new[++i] && !(start != -1 && stop != -1))
		if (((start != -1 || stop != -1) && glob->new[i] == '{')
		|| (start == -1 && glob->new[i] == '}'))
			return (FALSE);
		else if (glob->new[i] == '{')
			start = i;
		else if (glob->new[i] == '}')
			stop = i;
	if (start != -1 && stop != -1
	&& sh_glob_brackets_left_right(glob, start + 1, stop - 1))
	{
		glob->before = ft_strdups(glob->new);
		glob->before[start - 1] = '\0';
		glob->after = ft_strdups(glob->new + stop + 1);
		return ((ft_isint(glob->left))
		? sh_glob_brackets_rp_num(glob) : sh_glob_brackets_rp_alpha(glob));
	}
	return (FALSE);
}
