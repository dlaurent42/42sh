/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 00:19:57 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/09 22:09:37 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_history(t_shell *sh, char **argv)
{
	int		i;

	i = 0;
	if (!argv || !argv[0])
		return (sh_history_print(sh));
	if (argv[0] && !is_option_string(argv[0], "cdspwarn"))
	{
		i += (argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
			? 1 : 0;
		if (!argv[i])
			return (sh_history_print(sh));
		if (argv[i + 1])
			return (sh_history_error(2));
		if (!ft_isint(argv[i]) || (i = ft_atoi(argv[i])) == INT32_MIN)
			return (sh_history_error(1));
		if (i < 0)
			i *= (-1);
		return (sh_history_print_shift(sh, i));
	}
	return (sh_history_options(sh, argv));
}
