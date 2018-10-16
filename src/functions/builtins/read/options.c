/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 19:44:07 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 14:13:02 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	sh_read_options_verif(int **opt, char **prompt, char res)
{
	if ((*opt)[READ_U] <= 2)
		(*opt)[READ_U] = 0;
	if ((*opt)[READ_D] == -1 || (*opt)[READ_U] > 2)
		(*opt)[READ_D] = '\n';
	if ((*opt)[READ_E] == 0 && (*opt)[READ_U] == 0)
		(*opt)[READ_E] = -1;
	if ((*opt)[READ_P] == 0 && (*opt)[READ_U] == 0)
		(*opt)[READ_P] = -1;
	if ((*opt)[READ_P] == 0 && res == 0)
		ft_putstr_fd(*prompt, 2);
	return (res);
}

static char	sh_read_options_check(char **argv, int *i, int *j, int **opt)
{
	if (argv[*i][*j] == 'd' && !argv[*i][*j + 1])
		return (sh_read_option_d(argv, i, j, opt));
	else if (argv[*i][*j] == 'e' && (*j = *j + 1))
		return (((*opt)[READ_E] = 0));
	else if (argv[*i][*j] == 'n' && !argv[*i][*j + 1])
		return (sh_read_option_n(argv, i, j, opt));
	else if (argv[*i][*j] == 'r' && (*j = *j + 1))
		return (((*opt)[READ_R] = 0));
	else if (argv[*i][*j] == 's' && (*j = *j + 1))
		return (((*opt)[READ_S] = 0));
	else if (argv[*i][*j] == 't' && !argv[*i][*j + 1])
		return (sh_read_option_t(argv, i, j, opt));
	else if (argv[*i][*j] == 'u' && !argv[*i][*j + 1])
		return (sh_read_option_u(argv, i, j, opt));
	else
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
		if (ft_strcmps(argv[*i], "--") == 0 && (*i += 1))
			return (sh_read_options_verif(options, prompt, res));
		while (res == 0 && argv[*i] && argv[*i][j] && j)
			if (argv[*i][j] == 'p' && !argv[*i][j + 1])
			{
				(*options)[READ_P] = 0;
				res = sh_read_option_p(argv, i, &j, prompt);
			}
			else
				res = sh_read_options_check(argv, i, &j, options);
		*i += (res == 0 && argv[*i]) ? 1 : 0;
	}
	return (sh_read_options_verif(options, prompt, res));
}
