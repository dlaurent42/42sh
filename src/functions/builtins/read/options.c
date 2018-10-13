/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:44:07 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/13 19:58:06 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		sh_read_options(char **argv, int *i, int **options)
{
	int		j;
	char	res;

	res = 0;
	while (argv && argv[*i] && argv[*i][0] == '-' && (j = 1) == 1)
	{
		if (res != 0)
			return (res);
		if (ft_strcmps(argv[*i], "--") == 0)
			return ((*i += 1) == 0);
		while (argv[*i][j])
		{
			if (argv[*i][j] == 's')
				*options[READ_S] = 0;
		}
		*i += (argv[*i]) ? 1 : 0;
	}
	return (0);
}
