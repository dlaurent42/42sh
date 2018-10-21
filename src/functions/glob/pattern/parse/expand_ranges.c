/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ranges.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:43:37 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/21 19:26:55 by dlaurent         ###   ########.fr       */
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

static char	*sh_glob_expand_ranges_rp(char *str, char *new, int start, int stop)
{
	ft_printf("...... sh_glob_expand_ranges_rp received: [%s] and [%s]\n", str, new);
	sh_glob_repatriate(str, start, stop - start + 1);
	ft_printf("...... sh_glob_expand_ranges_rp after repatriate: [%s] and [%s]\n", str, new);
	str = sh_glob_inject(str, new, start);
	ft_printf("...... sh_glob_expand_ranges_rp after injection: [%s] and [%s]\n", str, new);
	ft_strdel(&new);
	ft_printf("...... sh_glob_expand_ranges_rp returned: [%s]\n", str);
	ft_printf("...... sh_glob_expand_range returned: [%s]\n", str);
	return (str);
}

static char	*sh_glob_expand_reverse_range(char *str)
{
	int		i;
	char	c;
	char	*new_str;

	i = 0;
	c = 32;
	new_str = NULL;
	ft_printf("...... sh_glob_reverse_range received: [%s]\n", str);
	while (c < 127)
	{
		if (c != '/' && ft_strcountif(str, c) == 0)
			new_str = sh_glob_joinchar(new_str, c);
		c++;
	}
	ft_strdel(&str);
	ft_printf("...... sh_glob_reverse_range returned: [%s]\n", new_str);
	return (new_str);
}

static char	*sh_glob_expand_range(char *str, int start, int stop)
{
	int		i;
	char	c;
	char	*new_str;

	i = start;
	new_str = NULL;
	c = 0;
	ft_printf("...... sh_glob_expand_range received: [%s] (start = %d and stop = %d)\n", str, start, stop);
	while (i <= stop)
	{
		if (i + 2 <= stop && str[i + 1] == '-'
		&& str[i] < str[i + 2] && (c = str[i]))
		{
			while (c <= str[i + 2])
			{
				(c != '/') ? new_str = sh_glob_joinchar(new_str, c) : 0;
				c++;
			}
			i += 2;
		}
		else
			new_str = sh_glob_joinchar(new_str, str[i]);
		i++;
	}
	if (ft_strcountif(new_str, '/'))
	{
		ft_printf("...... sh_glob_expand_range returned error '/' (%s)\n", new_str);
		ft_strdel(&new_str);
		return (str);
	}
	if (new_str && new_str[0] == '!')
		return (sh_glob_expand_ranges_rp(str, sh_glob_expand_reverse_range(new_str), start, stop));
	return (sh_glob_expand_ranges_rp(str, new_str, start, stop));
}

char		*sh_glob_expand_ranges(char *str)
{
	int		i;
	int		j;

	i = 0;
	ft_printf("... sh_glob_expand_ranges received: [%s]\n", str);
	while (str[i])
	{
		if (str[i] == '[' && !glob_is_esc(str, i))
		{
			j = i + 1;
			while (str[j])
			{
				if (str[j] == ']' && !glob_is_esc(str, i)
				&& (str[j - 1] != '[' || glob_is_esc(str, i - 1)))
				{
					str = sh_glob_expand_range(str, i + 1, j - 1);
					break ;
				}
				j++;
			}
		}
		i++;
	}
	ft_printf("... sh_glob_expand_ranges returned: [%s]\n", str);
	return (str);
}
