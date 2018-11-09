/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:16:13 by dlaurent          #+#    #+#             */
/*   Updated: 2018/11/09 20:56:23 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool		check_list(char c, char idx, char **lst)
{
	int				i;
	int				lst_len;
	unsigned char	index;
	bool			neg;

	i = 0;
	lst_len = 0;
	index = (unsigned char)idx;
	while (lst[lst_len])
		lst_len++;
	if (index > lst_len)
		return (FALSE);
	neg = (lst[(int)index - 1][0] == '!') ? TRUE : FALSE;
	while (lst[(int)index - 1][i])
	{
		if (lst[(int)index - 1][i] == c && neg == FALSE)
			return (TRUE);
		else if (lst[(int)index - 1][i] == c && neg == TRUE)
			return (FALSE);
		i++;
	}
	if (neg)
		return (TRUE);
	return (FALSE);
}

static bool		check_combinaisons(int i, int j, char **s, char **lst)
{
	if (s[0][i] != '\0')
	{
		if (s[1][j] == '\0')
			return (FALSE);
		else if (s[1][j] == '*' && !lexer_is_esc(s[1], j)
		&& check_combinaisons(i, j + 1, s, lst) == 0)
			return (check_combinaisons(i + 1, j, s, lst));
		else if (s[1][j] == '*' && !lexer_is_esc(s[1], j))
			return (check_combinaisons(i, j + 1, s, lst));
		else if (s[0][i] == s[1][j] || (s[1][j] == '?'
		&& !lexer_is_esc(s[1], j))
		|| (s[1][j] < 32 && check_list(s[0][i], s[1][j], lst)))
			return (check_combinaisons(i + 1, j + 1, s, lst));
		return (FALSE);
	}
	else if (s[0][i] == '\0')
	{
		if (s[1][j] == '\0')
			return (TRUE);
		else if (s[1][j] == '*')
			return (check_combinaisons(i, j + 1, s, lst));
		return (FALSE);
	}
	return (FALSE);
}

bool			glob_match(char *s1, char *s2, char **lst)
{
	char	res;
	char	**s;

	if (!(s = (char **)ft_memalloc(sizeof(char *) * 2)))
		return (FALSE);
	s[0] = s1;
	s[1] = s2;
	res = check_combinaisons(0, 0, s, lst);
	free(s);
	return (res);
}
