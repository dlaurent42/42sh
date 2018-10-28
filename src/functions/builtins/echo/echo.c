/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:20:20 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/27 23:30:43 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/*
** Display message on screen, writes each given STRING to standard output,
** with a space between each and a newline after the last one.
**
** -----------------------------------------------------------------------------
**
** Syntax
**      echo [options]... [string]...
**
** Options
**
**  -n
**      Do not output the trailing newline.
*/

static char	*sh_echo_concat_args(char **argv)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	while (argv && argv[i])
	{
		s = (s) ? ft_strjoinf(s, " ", 1) : 0;
		s = ft_strjoinf(s, argv[i], 1);
		i++;
	}
	return (s);
}

static char	*sh_echo_backslash_c(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\\' && s[i + 1] == 'c')
		{
			s[i] = '\0';
			break ;
		}
		i++;
	}
	return (s);
}

char		sh_echo(t_shell *sh, t_env *env, char **argv)
{
	int		current;
	char	option_n;
	char	*string;

	(void)sh;
	(void)env;
	current = 0;
	option_n = FALSE;
	string = NULL;
	while (argv[current] && argv[current][0] == '-'
	&& (argv[current][1] == 'n' || argv[current][1] == '-')
	&& !argv[current][2])
	{
		current++;
		if (argv[current - 1][1] == 'n')
			option_n = TRUE;
		else
			break ;
	}
	string = sh_echo_concat_args(argv + current);
	if (!option_n)
		string = ft_strjoinf(string, "\n", 1);
	ft_putstr(sh_echo_backslash_c(string));
	ft_strdel(&string);
	return (0);
}
