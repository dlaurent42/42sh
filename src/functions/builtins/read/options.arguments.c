/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 23:17:30 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/15 10:13:27 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	sh_read_option_d(char **argv, int *i, int *j, int **opt)
{
	*j = 0;
	*i = *i + 1;
	if (!argv[*i])
		return (sh_read_error('d', 2));
	ft_printf("Reading option d based on %s\n", argv[*i]);
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
	ft_printf("Reading option n based on %s\n", argv[*i]);
	if ((n = ft_atoi(argv[*i])) <= 0 || !ft_isint(argv[*i]))
		return (sh_read_error((char)n, 3));
	ft_printf("n equal %d\n", n);
	(*opt)[READ_N] = n;
	ft_printf("(*)opt[READ_N] equal %d\n", n);
	*i = *i + 1;
	return (0);
}

char	sh_read_option_p(char **argv, int *i, int *j, char **prompt)
{
	*j = 0;
	*i = *i + 1;
	if (!argv[*i])
		return (sh_read_error('p', 2));
	ft_printf("Reading option p based on %s\n", argv[*i]);
	if (!(*prompt = ft_strdups(argv[*i])))
		return (sh_read_error(0, 4));
	ft_printf("Prompt is %s\n", *prompt);
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
	ft_printf("Reading option t based on %s\n", argv[*i]);
	if ((n = ft_atoi(argv[*i])) < 0 || !ft_isint(argv[*i]))
		return (sh_read_error(n, 5));
	ft_printf("n equal %d\n", n);
	if (n == 0)
	{
		ft_printf("Reading option t return 1\n");
		return (1);
	}
	(*opt)[READ_T] = n;
	*i = *i + 1;
	ft_printf("Reading option t return 0\n");
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
	ft_printf("Reading option u based on %s\n", argv[*i]);
	if ((n = ft_atoi(argv[*i])) <= 0 || !ft_isint(argv[*i]))
		return (sh_read_error((char)n, 6));
	ft_printf("n equal %d\n", n);
	(*opt)[READ_U] = (n > 2) ? n : 0;
	if (n > 2 && (fcntl((*opt)[READ_U], F_GETFD)) == -1)
		return (sh_read_error((char)n, 7));
	*i = *i + 1;
	return (0);
}
