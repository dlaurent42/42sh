/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ranges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:43:37 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/24 16:57:48 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_glob_joinchar(char *str, char c)
{
	char	*new;

	if (!(new = ft_strnew(ft_strlens(str) + 2)))
		return (str);
	(str) ? new = ft_strcpy(new, str) : 0;
	new[ft_strlens(new)] = c;
	ft_strdel(&str);
	return (new);
}

static char	*sh_glob_expand_ranges_rp(
	t_filesystem *fs, char *str, int start, int stop)
{
	lexer_repatriate(str, start, stop - start + 1);
	str = lexer_inject_dup(str, &fs->curr_idx, start);
	return (str);
}

static char	*sh_glob_expand_range(
	t_filesystem *fs, char *str, int start, int stop)
{
	int		i;
	char	c;
	char	*new_str;

	i = start - 1;
	new_str = NULL;
	c = 0;
	while (++i <= stop)
		if (i + 2 <= stop && str[i + 1] == '-'
		&& str[i] < str[i + 2] && (c = str[i] - 1))
		{
			while (++c <= str[i + 2])
				(c != '/') ? new_str = sh_glob_joinchar(new_str, c) : 0;
			i += 2;
		}
		else
			new_str = sh_glob_joinchar(new_str, str[i]);
	if (ft_strcountif(new_str, '/'))
	{
		ft_strdel(&new_str);
		return (str);
	}
	(fs->curr_idx < GLOB_ASCII_MAX)
		? fs->lst[(int)fs->curr_idx++] = new_str : 0;
	return (sh_glob_expand_ranges_rp(fs, str, start - 1, stop + 1));
}

char		*sh_glob_expand_ranges(t_filesystem *fs, char *str)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '[' && !lexer_is_esc(str, i))
		{
			j = i + 1;
			while (str[j])
			{
				if (str[j] == ']' && !lexer_is_esc(str, i)
				&& (str[j - 1] != '[' || lexer_is_esc(str, i - 1)))
				{
					str = sh_glob_expand_range(fs, str, i + 1, j - 1);
					break ;
				}
				j++;
			}
		}
		i++;
	}
	return (str);
}
