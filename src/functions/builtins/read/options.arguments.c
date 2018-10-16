/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 23:17:30 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/16 16:29:41 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_read_option_d(char **argv, int *i, int *j, int **opt)
{
	*j = 0;
	*i = *i + 1;
	if (!argv[*i])
		return (sh_read_error('d', 2));
	(*opt)[READ_D] = argv[*i][*j];
	*i = *i + 1;
	return (0);
}

char	sh_read_option_n(char **argv, int *i, int *j, int **opt)
{
	int		n;

	n = 0;
	*j = 0;
	*i = *i + 1;
	if (!argv[*i])
		return (sh_read_error('n', 2));
	if ((n = ft_atoi(argv[*i])) <= 0 || !ft_isint(argv[*i]))
		return (sh_read_error((char)n, 3));
	(*opt)[READ_N] = n;
	*i = *i + 1;
	return (0);
}

char	sh_read_option_p(char **argv, int *i, int *j, char **prompt)
{
	*j = 0;
	*i = *i + 1;
	if (!argv[*i])
		return (sh_read_error('p', 2));
	if (!(*prompt = ft_strdups(argv[*i])))
		return (sh_read_error(0, 4));
	*i = *i + 1;
	return (0);
}

char	sh_read_option_t(char **argv, int *i, int *j, int **opt)
{
	int		n;

	n = 0;
	*j = 0;
	*i = *i + 1;
	if (!argv[*i])
		return (sh_read_error('t', 2));
	if ((n = ft_atoi(argv[*i])) < 0 || !ft_isint(argv[*i]))
		return (sh_read_error(n, 5));
	if (n == 0)
		return (1);
	(*opt)[READ_T] = n;
	*i = *i + 1;
	return (0);
}

char	sh_read_option_u(char **argv, int *i, int *j, int **opt)
{
	int		n;

	n = 0;
	*j = 0;
	*i = *i + 1;
	if (!argv[*i])
		return (sh_read_error('u', 2));
	if ((n = ft_atoi(argv[*i])) <= 0 || !ft_isint(argv[*i]))
		return (sh_read_error((char)n, 6));
	(*opt)[READ_U] = (n > 2) ? n : 0;
	if (n > 2 && (fcntl((*opt)[READ_U], F_GETFD)) == -1)
		return (sh_read_error((char)n, 7));
	*i = *i + 1;
	return (0);
}
