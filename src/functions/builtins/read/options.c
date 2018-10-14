/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:44:07 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/14 18:41:58 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_read_options_check(char **argv, int *i, int *j, int **opt)
{
	if (argv[*i][*j] == 'd' && !argv[*i][*j + 1])
		return (sh_read_option_d(argv, i, j, opt));
	// else if (argv[*i][*j] == 'e' && (*j = *j + 1))
	// {
	// 	*opt[READ_E] = 0;
	// 	return (0);
	// }
	else if (argv[*i][*j] == 'n' && !argv[*i][*j + 1])
		return (sh_read_option_n(argv, i, j, opt));
	else if (argv[*i][*j] == 'r' && (*j = *j + 1))
		return ((*opt[READ_R] = 0));
	else if (argv[*i][*j] == 's' && (*j = *j + 1))
		return ((*opt[READ_S] = 0));
	else if (argv[*i][*j] == 't' && !argv[*i][*j + 1])
		return (sh_read_option_t(argv, i, j, opt));
	else if (argv[*i][*j] == 'u' && !argv[*i][*j + 1])
		return (sh_read_option_u(argv, i, j, opt));
	return (sh_read_error(argv[*i][*j], 1));
}

char		sh_read_options(char **argv, int *i, int **options, char **prompt)
{
	int		j;
	char	res;

	res = 0;
	while (res == 0 && argv && argv[*i] && argv[*i][0] == '-' && argv[*i][1])
	{
		j = 1;
		if (res != 0)
			return (res);
		if (ft_strcmps(argv[*i], "--") == 0)
			return ((*i += 1) == 0);
		while (res == 0 && argv[*i] && argv[*i][j])
			if (argv[*i][j] == 'p' && !argv[*i][j + 1])
			{
				*options[READ_P] = 0;
				res = sh_read_option_p(argv, i, &j, prompt);
			}
			else
			{
				res = sh_read_options_check(argv, i, &j, options);
				ft_printf("res = %d\n", res);
			}
		*i += (res == 0 && argv[*i]) ? 1 : 0;
	}
	ft_printf("returning res = %d\n", res);
	return (res);
}
