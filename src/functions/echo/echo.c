/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:20:20 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/03 19:05:39 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_echo_parse_string(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			j = i;
			while (s[j])
			{
				s[j] = s[j + 1];
				j++;
			}
		}
		else
			i++;
	}
	return (s);
}

static char	*sh_echo_concat_args(char **argv)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	while (argv && argv[i])
	{
		s = ft_strjoinf(s, argv[i], 1);
		i++;
	}
	return (s);
}

char		sh_echo(t_shell *sh, char **argv)
{
	int		current;
	char	option_n;
	char	*string;

	current = 0;
	option_n = FALSE;
	string = NULL;
	while (argv[current] && argv[current] && argv[current][0] == '-')
	{
		if (argv[current][1] == 'n' && !argv[current][2])
			option_n = TRUE;
		current++;
	}
	string = sh_echo_concat_args(argv + current);
	string = sh_echo_parse_string(string);
	ft_putstr(string);
	return (0);
}
