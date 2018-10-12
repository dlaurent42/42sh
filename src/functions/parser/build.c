/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 12:57:03 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/12 19:12:15 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_command_get_isquote(char *s, int i, bool *dq, bool *sq)
{
	if (s[i] == '"' && i && s[i - 1] == '=' && !(*dq || *sq))
		*dq = 2;
	else if (s[i] == '\'' && i && s[i - 1] == '=' && !(*dq || *sq))
		*sq = 2;
	if (s[i] == '"' && !(*dq || *sq))
		*dq = 1;
	else if (s[i] == '\'' && !(*dq || *sq))
		*sq = 1;
	else if (s[i] == '"' && (*dq || *sq))
		*dq = 0;
	else if (s[i] == '"' && (*dq || *sq))
		*sq = 0;
}

static int	sh_command_opt_count(char *str)
{
	int		i;
	int		count;
	bool	in_dquote;
	bool	in_squote;

	i = 0;
	count = 0;
	in_dquote = FALSE;
	in_squote = FALSE;
	while (str[i])
	{
		sh_command_get_isquote(str, i, &in_dquote, &in_squote);
		if ((str[i] == ' ' || str[i] == '\t') && !in_dquote && !in_squote
		&& ++count)
			while (str[i + 1] && (str[i + 1] == ' ' || str[i + 1] == '\t'))
				i++;
		i += (str[i]) ? 1 : 0;
	}
	if (i && str[i - 1] != ' ' && str[i - 1] != '\t')
		return (count + 1);
	return (count);
}

static char	*sh_command_get_next_opt(char *s, int n)
{
	int		start;
	int		end;
	int		c;
	bool	q[2];

	start = 0;
	end = 0;
	c = 0;
	ft_bzero((void *)q, sizeof(bool) * 2);
	while (s[end])
	{
		sh_command_get_isquote(s, end, &q[0], &q[1]);
		if ((s[end] == ' ' || s[end] == '\t') && !q[0] && !q[1] && c == n - 1)
			return (ft_strsub(s, start, end - start));
		else if ((s[end] == ' ' || s[end] == '\t') && !q[0] && !q[1] && ++c)
		{
			while (s[end + 1] && (s[end + 1] == ' ' || s[end + 1] == '\t'))
				end++;
			start = end + 1;
		}
		end += (s[end]) ? 1 : 0;
	}
	if (end && s[end - 1] != ' ' && s[end - 1] != '\t')
		return (ft_strsub(s, start, end - start));
	return (NULL);
}

static char	**sh_command_buid_opt(char *str)
{
	int		i;
	int		n;
	char	**arr;

	i = 0;
	n = sh_command_opt_count(str);
	if (!(arr = (char **)ft_memalloc(sizeof(char *) * (n + 1))))
		return (NULL);
	while (i < n)
	{
		arr[i] = sh_command_get_next_opt(str, i + 1);
		i++;
	}
	return (arr);
}

char		**sh_command_build(char *str)
{
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	j = i;
	if (!str[i])
		return (NULL);
	return (sh_command_buid_opt(str + i));
}
