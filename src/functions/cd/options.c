/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:10:20 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/07 21:15:09 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			sh_cd_options(char **argv, bool *opt_l, bool *opt_p)
{
	int		i;
	int		j;

	i = 0;
	while (argv[i] && argv[i][0] == '-' && is_option_string(argv[i], "LP"))
	{
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] == 'L')
				*opt_l = TRUE;
			else if (argv[i][j] == 'P')
				*opt_p = TRUE;
			j++;
		}
		i++;
	}
	if (argv[i] && argv[i][0] == '-' && argv[i][1] == '-' && !argv[i][2])
		return (i + 1);
	return (i);
}
