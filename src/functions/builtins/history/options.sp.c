/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.sp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 16:47:40 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/09 21:35:46 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_history_sp(t_shell *sh, char **argv, bool opt_s, bool opt_p)
{
	int		i;
	char	*s;

	i = 0;
	s = NULL;
	if (!argv || !argv[0])
		return (0);
	while (argv[i])
	{
		s = (s) ? ft_strjoinf(s, " ", 1) : NULL;
		s = ft_strjoinf(s, argv[i], 1);
		i++;
	}
	if (!s)
		return (0);
	if (opt_s)
		command_add_str_based(sh, s, true);
	if (opt_p)
		ft_putendl(s);
	ft_strdel(&s);
	return (0);
}

char		sh_history_option_sp(t_shell *sh, int *i, int *j, char **argv)
{
	bool	option_s;
	bool	option_p;

	option_s = FALSE;
	option_p = FALSE;
	while (argv[*i][*j])
	{
		if (argv[*i][*j] == 's')
			option_s = TRUE;
		else if (argv[*i][*j] == 'p')
			option_p = TRUE;
		else
			return (0);
		*j = *j + 1;
	}
	*i = *i + 1;
	return (sh_history_sp(sh, argv + *i, option_s, option_p));
}
