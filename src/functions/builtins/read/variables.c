/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 00:07:16 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/15 10:28:02 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static bool	sh_read_valid_var(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (!ft_isalpha(s[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char		sh_read_variables(char **argv, int *i, char ***vars)
{
	int	j;

	j = 0;
	while (argv[*i])
	{
		if (!sh_read_valid_var(argv[*i]))
			return (sh_read_error_msg(argv[*i], 1));
		if (j >= READ_MAX_VAR)
		{
			ft_printf("Too much variables, exit\n");
			return (0);
		}
		(*vars)[j] = ft_strdups(argv[*i]);
		ft_printf("Var %d set to %s\n", j, (*vars)[j]);
		*i = *i + 1;
		j++;
	}
	return (0);
}
