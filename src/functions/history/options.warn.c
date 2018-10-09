/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.warn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:32:31 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 10:19:41 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	sh_history_option_w(t_shell *sh, char *file)
{
	(void)sh;
	(void)file;
}

static void	sh_history_option_a(t_shell *sh, char *file)
{
	(void)sh;
	(void)file;
}

static void	sh_history_option_r(t_shell *sh, char *file)
{
	(void)sh;
	(void)file;
}

static void	sh_history_option_n(t_shell *sh, char *file)
{
	(void)sh;
	(void)file;
}

char		sh_history_option_warn(t_shell *sh, int *i, int *j, char **argv)
{
	if (argv[*i][*j + 1] != '\0')
		return (0);
	if (argv[*i][*j] == 'w')
		(argv[*i + 1] && argv[*i + 1][0] == '.')
			? sh_history_option_w(sh, argv[*i + 1])
			: sh_history_option_w(sh, NULL);
	if (argv[*i][*j] == 'a')
		(argv[*i + 1] && argv[*i + 1][0] == '.')
			? sh_history_option_a(sh, argv[*i + 1])
			: sh_history_option_a(sh, NULL);
	if (argv[*i][*j] == 'r')
		(argv[*i + 1] && argv[*i + 1][0] == '.')
			? sh_history_option_r(sh, argv[*i + 1])
			: sh_history_option_r(sh, NULL);
	if (argv[*i][*j] == 'n')
		(argv[*i + 1] && argv[*i + 1][0] == '.')
			? sh_history_option_n(sh, argv[*i + 1])
			: sh_history_option_n(sh, NULL);
	return (0);
}
